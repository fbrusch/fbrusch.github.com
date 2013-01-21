from pystache import render
from glob import glob
import codecs


def build_index():
    index_template = open("index.md.mustache").read()
    index = render(index_template, {"code_files": [{"code_file_show": x+".html",
                                                    "code_file_download": x} for x in
                                           glob("*.c")]})
    open("index.md","w").write(index)

def build_files_md():
    c_files = glob("*.c")
    c_file_template = codecs.open("code_file.md.mustache","r","UTF-8").read()
    for f in c_files:
        hash = {"file_content": unicode(codecs.open(f,"r","UTF-8").read()),
                "file_name": f}
        codecs.open(f+".md", "w", "UTF-8").write(render (c_file_template, hash))

def build():
    build_files_md()
    build_index()
