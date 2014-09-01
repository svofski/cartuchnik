#!/opt/local/bin/python
#
# SVG to C hack by Frank Buss http://www.frank-buss.de/vectrex/
#
import re
import xml.etree.ElementTree as etree
import math

def stripNamespace(x):
    return re.sub('{[^}]+}', '', x)

xl = 0
yl = 0

def printCmd(cmd, x, y):
    if x != 0 or y != 0:
        print "\t%d, %d, %d," % (cmd, y, x)

def lineTo(x, y):
    global xl
    global yl
    x = int(x)
    y = int(y)
    printCmd(0xff, x - xl, yl - y)
    xl = x
    yl = y

def moveTo(x, y):
    global xl
    global yl
    x = int(x)
    y = int(y)
    printCmd(0, x - xl, yl - y)
    xl = x
    yl = y

def parsePath(p):
    x = 0
    y = 0
    xs = 0
    ys = 0
    tmp = 0
    state = 0
    p = re.sub(',', ' ', p)
    p = re.sub('  ', ' ', p)
    first = True
    relative = True
    curveMode = False
    for item in p.split(' '):
        #item = item.lower()
        if state == 0:
            if item == 'm':
                first = True
                curveMode = False
                relative = True
            elif item == 'M':
                first = True
                curveMode = False
                relative = False
            elif item == 'c':
                curveMode = True
                relative = True
            elif item == 'z':
                x = xs
                y = ys
                curveMode = False
                lineTo(x, y)
            elif item == 'l':
                curveMode = False
                relative = True
                state = state
            elif item == 'L':
                curveMode = False
                relative = False
                state = state
            else:
                tmp = float(item)
                if curveMode:
                    state = 3
                else:
                    state = 2
        elif state == 2:
            if relative:
                x = x + tmp
                y = y + float(item)
            else:
                x = tmp
                y = float(item)
            if first:
                xs = x
                ys = y
                moveTo(x, y)
                first = False
            else:
                lineTo(x, y)
            state = 0
        elif state == 3:
            # 1st y
            state = 4
        elif state == 4:
            # 2nd x
            tmp = float(item)
            state = 5
        elif state == 5:
            # 2nd y
            tmp = float(item)
            state = 6
        elif state == 6:
            # 3nd x
            tmp = float(item)
            state = 7
        elif state == 7:
            # 3nd y
            if relative:
                x = x + tmp
                y = y + float(item)
            else:
                x = tmp
                y = float(item)
            if first:
                xs = x
                ys = y
                moveTo(x, y)
                first = False
            else:
                lineTo(x, y)
            state = 0

print "uint8_t path[] = {"
tree = etree.parse('test.svg')
root = tree.getroot()
for child in root:
    name = stripNamespace(child.tag)
    if name == 'g':
        for child2 in child:
            name = stripNamespace(child2.tag)
            if name == 'path':
                parsePath(child2.attrib['d'])

print "\t1"
print "};"

m = 80
a = 20
for i in range(0, m):
    print "%d," % (int(math.sin(2 * math.pi / m * i) * a))
