# linux mingw32 build
import os
import shutil

def RelcopyAllFilesTo(src, dst):
    if not os.path.exists(src):
        #print(f"??????: ???????? ????? {src} ?? ??????????")
        return
    
    src_folder_name = os.path.basename(src)
    target_path = os.path.join(dst, src_folder_name)
    if os.path.exists(target_path):
        shutil.rmtree(target_path)
    
    shutil.copytree(
        src, 
        target_path,
        ignore=shutil.ignore_patterns('Thumbs.db', 'thumbs.db')
    )


def copyAllFilesTo(src, dst):
	for root, dirs, files in os.walk(src):
		for filename in files:
			if filename.lower() == 'thumbs.db':
				continue
			source_path = os.path.join(root, filename)
			destination_path = os.path.join(dst, filename)
			shutil.copy2(source_path, destination_path)
	
copyAllFilesTo("src", "tmp")
RelcopyAllFilesTo("third_party/glew", "tmp")
RelcopyAllFilesTo("third_party/stb", "tmp")
RelcopyAllFilesTo("third_party/freeglut", "tmp")

RelcopyAllFilesTo("img", "build")
shutil.copy2("Makefile", "tmp");
	
os.chdir("tmp")
os.system("make linux")
shutil.copy2("main.exe", "../build");
	
os.chdir("../")
shutil.rmtree("tmp")
os.makedirs("tmp")
	
	
