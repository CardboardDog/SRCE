# this is a reminder that i should have used java or pyQt5
import srcelib
import tkinter
from tkinter import filedialog
from tkinter import simpledialog
import pygame
pygame.init()
textures = {}
levels = {}
display = pygame.display.set_mode((800,600))
pygame.display.set_caption("SRCE Game Editor")
running = True
editing = False
textFont = pygame.font.SysFont(None,45)
smallFont = pygame.font.SysFont(None,20)
tinyFont = pygame.font.SysFont(None,15)
mousePosition = pygame.mouse.get_pos()
mouseClicked = False
filePath = ""
tab = "textures"
levelTab = 0
scrollY = 0
texScroll = 0
textureI = 0
openTexture = None
colorSelect = 0
drawMode = 0
levelTool = (0,0)
lastAt = (None,None)
editMode = 0
startRect = (None, None)
currentRect = (None,None)
scaleX = 0
scaleY = 0
tk = tkinter.Tk()
tk.withdraw()
def open_file():
    global filePath
    global textures
    global levels
    global tk
    global scaleX
    global scaleY
    filePath = filedialog.askopenfilename()
    textures = srcelib.read_file_textures(filePath)
    levels = srcelib.read_file_levels(filePath)
    scaleDat = srcelib.load_level_size(filePath,None)
    scaleX = scaleDat[2]
    scaleY = scaleDat[3]
while running:
    # controls
    mousePosition = pygame.mouse.get_pos()
    scrollY = 0
    for event in pygame.event.get():
        if(event.type == pygame.QUIT):
            running = False
        elif (event.type == pygame.MOUSEBUTTONDOWN):
            mouseClicked = True
        elif (event.type == pygame.MOUSEBUTTONUP):
            mouseClicked = False
        elif (event.type == pygame.MOUSEWHEEL):
            scrollY = event.y
    pygame.draw.rect(display,(25,25,25),(0,0,800,600))
    if(not editing):
        # startup screen
        fontRender = textFont.render("New",False,(255,255,255))
        pygame.draw.rect(display,(50,50,50),(410,300,100,25))
        display.blit(fontRender,(410,300))
        fontRender = textFont.render("Load",False,(255,255,255))
        pygame.draw.rect(display,(50,50,50),(290,300,100,25))
        display.blit(fontRender,(290,300))
        if(mousePosition[0]>410 and mousePosition[0]<510 and mousePosition[1]>300 and mousePosition[1]<325 and mouseClicked):
            scaleX = simpledialog.askinteger("Level Scale","X:",initialvalue=24)
            scaleY = simpledialog.askinteger("Level Scale","Y:",initialvalue=24)
            editing = True
        elif(mousePosition[0]>290 and mousePosition[0]<390 and mousePosition[1]>300 and mousePosition[1]<325 and mouseClicked):
            open_file()
            editing = True
    else:
        # tabs and tab buttons
        x=0
        for tabs in ["textures","levels","settings"]:
            fontRender = textFont.render(tabs,False,(255,255,255))
            pygame.draw.rect(display,(50,50,50),(x,0,125,25))
            display.blit(fontRender,(x,0))
            if(mousePosition[0]>x and mousePosition[0]<x+125 and mousePosition[1]>0 and mousePosition[1]<25 and mouseClicked):
                tab = tabs
                texScroll = 0
                scrollY = 0
                openTexture = None
            x+=135
        if(tab == "textures"):
            y=65
            i=0
            # some buttons and panels
            pygame.draw.rect(display,(35,35,35),(0,35,200,160))
            fontRender = textFont.render("textures:",False,(255,255,255))
            pygame.draw.rect(display,(50,50,50),(0,(35+160+20),30,30))
            pygame.draw.rect(display,(50,50,50),(0+40,(35+160+20),30,30))
            pygame.draw.rect(display,(50,50,50),(0+80,(35+160+20),30,30))
            display.blit(fontRender,(0,35))
            fontRender = smallFont.render("New",False,(255,255,255))
            display.blit(fontRender,(0,(35+160+20)))
            fontRender = smallFont.render("Dele",False,(255,255,255))
            display.blit(fontRender,(40,(35+160+20)))
            fontRender = smallFont.render("Ren",False,(255,255,255))
            display.blit(fontRender,(80,(35+160+20)))
            # ren, del, new textures.
            if(mousePosition[0]>0 and mousePosition[0]<30 and mousePosition[1]>35+160+20 and mousePosition[1]<25+160+30+20 and mouseClicked):
                dTex = [[0 for x in range(65)] for y in range(65)]
                openTexture = "ntex"+str(textureI)
                textures["ntex"+str(textureI)] = dTex
                mouseClicked = False
                textureI += 1
            if(mousePosition[0]>40 and mousePosition[0]<70 and mousePosition[1]>35+160+20 and mousePosition[1]<25+160+30+20 and mouseClicked and not openTexture == None):
                del textures[openTexture]
                openTexture = None
                mouseClicked = False
            if(mousePosition[0]>80 and mousePosition[0]<120 and mousePosition[1]>35+160+20 and mousePosition[1]<25+160+30+20 and mouseClicked and not openTexture == None):
                if(not openTexture == None):
                    newName = simpledialog.askstring("Texture Name","Rename Texture:",initialvalue=openTexture)
                    if(not newName == None):
                        if not newName in textures:
                            startRect = (None,None)
                            mouseClicked = False
                            textures[newName] = textures.pop(openTexture)
                            openTexture = newName
            # scroll through textures
            if(texScroll<0):
                texScroll = 0
            for tex in range(0,len(textures)):
                if((tex+texScroll)<len(textures) and i<5):
                    fontRender = smallFont.render(list(textures)[tex+texScroll],False,(255,255,255))
                    pygame.draw.rect(display,(50,50,50),(0,y,200,25))
                    display.blit(fontRender,(0,y))
                    if(mousePosition[0]>0 and mousePosition[0]<200 and mousePosition[1]>y and mousePosition[1]<y+30 and mouseClicked):
                        openTexture = list(textures)[tex+texScroll]
                    y+=30
                    i+=1
            if(mousePosition[0]>0 and mousePosition[0]<200 and mousePosition[1]>65 and mousePosition[1]<265):
                texScroll-=scrollY
            if(texScroll<0):
                texScroll = 0
            if(texScroll+5>len(textures)-1):
                texScroll = len(textures)-5
            # texture editing and rendering
            if(not openTexture == None):
                for x in range(0,64):
                    for y in range(0,64):
                        if not textures[openTexture][x][y] == 35:
                            pygame.draw.rect(display,(srcelib.palette[textures[openTexture][x][y]][0],srcelib.palette[textures[openTexture][x][y]][1],srcelib.palette[textures[openTexture][x][y]][2]),(200+(x*8),35+(y*8),8,8))
                        if(mousePosition[0]>200+(x*8) and mousePosition[0]<200+(x*8)+8 and mousePosition[1]>35+(y*8) and mousePosition[1]<35+(y*8)+8 and mouseClicked):
                            if(drawMode == 0):
                                textures[openTexture][x][y] = colorSelect
                            if(drawMode == 1):
                                textures[openTexture][x][y] = 35
                            if(drawMode == 2):
                                if startRect == (None,None):
                                    startRect = (x,y)
                                    currentRect = (x,y)
                                else:
                                    currentRect = (x,y)
                if not currentRect == (None,None):
                    nRect = pygame.rect.Rect(200+(startRect[0]*8),35+(startRect[1]*8),(currentRect[0]-startRect[0])*8,(currentRect[1]-startRect[1])*8)
                    nRect.normalize()
                    pygame.draw.rect(display,(255,255,255),nRect,2)
                    if(not mouseClicked):
                            for xx in range(startRect[0],currentRect[0]):
                                for yy in range(startRect[1],currentRect[1]):
                                    textures[openTexture][xx][yy] = colorSelect
                            startRect = (None,None)
                            currentRect = (None,None)
            # palette
            for x in range(0,int(len(srcelib.palette)/4)):
                for y in range(0,4):
                    pygame.draw.rect(display,(srcelib.palette[x+((y*5))][0],srcelib.palette[x+((y*5))][1],srcelib.palette[x+((y*5))][2]),(712+(x*18),35+(y*18),18,18))
                    if(colorSelect == x+((y*5))):
                        if(not (255-srcelib.palette[x+((y*5))][0]) == 128):
                            pygame.draw.rect(display,(255-srcelib.palette[x+((y*5))][0],255-srcelib.palette[x+((y*5))][1],255-srcelib.palette[x+((y*5))][2]),(712+(x*18),35+(y*18),18,18),2)
                        else:
                            pygame.draw.rect(display,(0,0,0),(712+(x*18),35+(y*18),18,18),2)
                    if(mousePosition[0]>712+(x*18) and mousePosition[0]<712+(x*18)+18 and mousePosition[1]>35+(y*18) and mousePosition[1]<35+(y*18)+18 and mouseClicked):
                        colorSelect = x+((y*5))
            letterX = 0
            # draw erase and rectangle tools
            for letter in ["D","E","R"]:
                pygame.draw.rect(display,(50,50,50),(712+letterX,107,18,18))
                if letterX/18 == drawMode:
                    pygame.draw.rect(display,(255,255,255),(712+letterX,107,18,18),2)
                if(mousePosition[0]>712+letterX and mousePosition[0]<712+letterX+18 and mousePosition[1]>107 and mousePosition[1]<107+18 and mouseClicked):
                    drawMode = letterX/18
                    startRect = (None,None)
                fontRender = smallFont.render(letter,False,(255,255,255))
                display.blit(fontRender,(712+letterX,107))
                letterX += 18
        elif(tab == "levels"):
            i=0
            y=65
            # some buttons and panels
            pygame.draw.rect(display,(35,35,35),(0,35,200,160))
            pygame.draw.rect(display,(50,50,50),(0,(35+160+20),30,30))
            pygame.draw.rect(display,(50,50,50),(0+40,(35+160+20),30,30))
            pygame.draw.rect(display,(50,50,50),(0+80,(35+160+20),30,30))
            fontRender = textFont.render("levels:",False,(255,255,255))
            display.blit(fontRender,(0,35))
            fontRender = smallFont.render("New",False,(255,255,255))
            display.blit(fontRender,(0,(35+160+20)))
            fontRender = smallFont.render("Dele",False,(255,255,255))
            display.blit(fontRender,(40,(35+160+20)))
            fontRender = smallFont.render("Ren",False,(255,255,255))
            display.blit(fontRender,(80,(35+160+20)))
            # scroll through levels
            if(texScroll<0):
                texScroll = 0
            for tex in range(0,len(levels)):
                if((tex+texScroll)<len(levels) and i<5):
                    fontRender = smallFont.render(list(levels)[tex+texScroll],False,(255,255,255))
                    pygame.draw.rect(display,(50,50,50),(0,y,200,25))
                    display.blit(fontRender,(0,y))
                    if(mousePosition[0]>0 and mousePosition[0]<200 and mousePosition[1]>y and mousePosition[1]<y+30 and mouseClicked):
                        openTexture = list(levels)[tex+texScroll]
                    y+=30
                    i+=1
            if(mousePosition[0]>0 and mousePosition[0]<200 and mousePosition[1]>65 and mousePosition[1]<265):
                texScroll-=scrollY
            if(texScroll<0):
                texScroll = 0
            if(texScroll+5>len(levels)-1):
                texScroll = len(levels)-5
            # del, ren, new levels
            if(mousePosition[0]>0 and mousePosition[0]<30 and mousePosition[1]>35+160+20 and mousePosition[1]<25+160+30+20 and mouseClicked):
                xStrPos = simpledialog.askinteger("Start Pos","Start X:",initialvalue=0)
                yStrPos = simpledialog.askinteger("Start Pos","Start Y:",initialvalue=0)
                dTex = ((xStrPos,yStrPos,scaleX,scaleY),
                    [[0 for x in range(scaleX)] for y in range(scaleY)],
                    [[0 for x in range(scaleX)] for y in range(scaleY)],
                    [[0 for x in range(scaleX)] for y in range(scaleY)])
                openTexture = "nlev"+str(textureI)
                levels["nlev"+str(textureI)] = dTex
                mouseClicked = False
                textureI += 1
            if(mousePosition[0]>40 and mousePosition[0]<70 and mousePosition[1]>35+160+20 and mousePosition[1]<25+160+30+20 and mouseClicked and not openTexture == None):
                del levels[openTexture]
                openTexture = None
                mouseClicked = False
            if(mousePosition[0]>80 and mousePosition[0]<120 and mousePosition[1]>35+160+20 and mousePosition[1]<25+160+30+20 and mouseClicked and not openTexture == None):
                if(not openTexture == None):
                    newName = simpledialog.askstring("Texture Name","Rename Texture:",initialvalue=openTexture)
                    if(not newName == None):
                        if not newName in levels:
                            startRect = (None,None)
                            mouseClicked = False
                            levels[newName] = levels.pop(openTexture)
                            openTexture = newName
            # level floor, roof, surface select
            pygame.draw.rect(display,(50,50,50),(0+40,(35+160+55),30,30))
            fontRender = smallFont.render("Cei",False,(255,255,255))
            display.blit(fontRender,(40,(35+160+55)))
            pygame.draw.rect(display,(50,50,50),(0,(35+160+55),30,30))
            fontRender = smallFont.render("Gro",False,(255,255,255))
            display.blit(fontRender,(0,(35+160+55)))
            if(mousePosition[0]>0 and mousePosition[0]<30 and mousePosition[1]>35+160+55 and mousePosition[1]<25+160+30+55 and mouseClicked and not openTexture == None):
                levelTab = 0
                mouseClicked = False
            if(mousePosition[0]>40 and mousePosition[0]<70 and mousePosition[1]>35+160+55 and mousePosition[1]<25+160+30+55 and mouseClicked and not openTexture == None):
                levelTab = 1
            # heightmap editor
            if(not openTexture == None):
                for x in range(0,levels[openTexture][0][2]):
                    for y in range(0,levels[openTexture][0][3]):
                        pygame.draw.rect(display,(int(255/35)*levels[openTexture][levelTab+1][x][y],(255/35)*levels[openTexture][levelTab+1][x][y],(255/35)*levels[openTexture][levelTab+1][x][y]),(200+(x*15),35+(y*15),15,15))
                        pygame.draw.rect(display,(0,255,0),(200+(x*15),35+(y*15),15,15),1)
                        fontRender = tinyFont.render(str(levels[openTexture][levelTab+1][x][y]),False,(0,255,0))
                        display.blit(fontRender,(200+(x*15)+2,35+(y*15)+2))
                        if (mousePosition[0]>200+(x*15) and mousePosition[0]<215+(x*15) and mousePosition[1]>35+(y*15) and mousePosition[1]<50+(y*15) and mouseClicked and not lastAt == (x,y)):
                            if(levelTool[0] == 0):
                                levels[openTexture][levelTab+1][x][y] = levelTool[1]
                            else:
                                levels[openTexture][levelTab+1][x][y] += levelTool[0]
                            if(levels[openTexture][levelTab+1][x][y] < 0):
                                levels[openTexture][levelTab+1][x][y] = 0
                            elif(levels[openTexture][levelTab+1][x][y] > 35):
                                levels[openTexture][levelTab+1][x][y] = 35
                            lastAt = (x,y)
            if not mouseClicked:
                lastAt = (None, None)
            # add or subtract
            pygame.draw.rect(display,(50,50,50),(0+80,(35+160+90),30,30))
            fontRender = smallFont.render("=",False,(255,255,255))
            display.blit(fontRender,(80,(35+160+90)))
            pygame.draw.rect(display,(50,50,50),(0+40,(35+160+90),30,30))
            fontRender = smallFont.render("+",False,(255,255,255))
            display.blit(fontRender,(40,(35+160+90)))
            pygame.draw.rect(display,(50,50,50),(0,(35+160+90),30,30))
            fontRender = smallFont.render("-",False,(255,255,255))
            display.blit(fontRender,(0,(35+160+90)))
            if(mousePosition[0]>0+80 and mousePosition[0]<0+80+30 and mousePosition[1]>(35+160+90) and mousePosition[1]<(35+160+90)+30 and mouseClicked):
                levelTool = (0,simpledialog.askinteger("Flatten Tool","Flatten To:",initialvalue=0))
                mouseClicked = False
            if(mousePosition[0]>0+40 and mousePosition[0]<0+40+30 and mousePosition[1]>(35+160+90) and mousePosition[1]<(35+160+90)+30 and mouseClicked):
                levelTool = (1,0)
            if(mousePosition[0]>0 and mousePosition[0]<30 and mousePosition[1]>(35+160+90) and mousePosition[1]<(35+160+90)+30 and mouseClicked):
                levelTool = (-1,0)
            elif(tab == "settings"):
                pass #the ketchup
    pygame.display.flip()
pygame.quit()
