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
        tests = False
        for line in file.readlines():
            if "TESTS" in line:
                tests = True
                break
            collection.write(line)
        if not tests:
            print(f"Warning: File {path} doesn't contain TESTS")

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
