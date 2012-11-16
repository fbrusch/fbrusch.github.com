from pystache import render
from yaml import load
from sys import argv
def render_page(template_file, content_file=None, data_file=None):
    template = open(template_file).read().encode('utf-8')
    content = (unicode(open(content_file).read(),'utf-8'))
    data = {}
    if data_file:
        data = load(open(data_file).read())
    data["main_content"] = content
    return render(template, data)

if __name__ == '__main__':
    out = render_page(argv[1],argv[2],argv[3])
    print out.encode('utf-8')
