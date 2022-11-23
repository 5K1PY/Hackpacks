#!/usr/bin/env python3
import os

BASE_PATH = ".."
TEMPLATE = "Template.cpp"

def adddir(dirname, files):
    for object in os.listdir(dirname):
        if object.startswith("."):
            continue
        
        path = os.path.join(dirname, object)
        if os.path.isdir(path):
            adddir(path, files)
        elif path.endswith(".cpp"):
            files.append(path)

def addfile(path):
    name = path.lstrip(BASE_PATH).lstrip("/").lstrip("\\").replace("\\", "/")
    collection.write("\\section{" + name + "}\n\n")
    collection.write("\\begin{spverbatim}\n")
    with open(path) as file:
        lines = file.readlines()

        skipstart = 0
        while path != template and "using namespace std;" not in lines[skipstart]:
            skipstart += 1
        skipstart += path != template

        while lines[skipstart].strip() == "":
            skipstart += 1

        skipend = len(lines)
        for i, line in enumerate(lines):
            if "TESTS" in line:
                skipend = i
        if skipend == len(lines) and path != template:
            print(f"Warning: File {path} doesn't contain TESTS")

        while lines[skipend-1].strip() == "":
            skipend -= 1

        for line in lines[skipstart:skipend]:
            collection.write(line)

    collection.write("\\end{spverbatim}\n")
    collection.write("\\pagebreak\n")

if __name__ == "__main__":
    with open("all.tex", "w") as collection:
        with open("begin.tex") as begin:
            collection.write(begin.read())

        files = []
        adddir(BASE_PATH, files)
        files.sort()

        template = os.path.join(BASE_PATH, TEMPLATE)
        files.remove(template)
        files = [template] + files
        for file in files:
            addfile(file)

        with open("end.tex") as end:
            collection.write(end.read())
