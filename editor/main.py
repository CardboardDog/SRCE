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
mousePosition = pygame.mouse.get_pos()
mouseClicked = False
filePath = ""
tab = "textures"
scrollY = 0
texScroll = 0
textureI = 0
openTexture = None
colorSelect = 0
drawMode = 0
startRect = (None, None)
currentRect = (None,None)
tk = tkinter.Tk()
tk.withdraw()
def open_file():
    global filePath
    global textures
    global tk
    filePath = filedialog.askopenfilename()
    textures = srcelib.read_file_textures(filePath)
    levels = srcelib.read_file_levels(filePath)
while running:
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
        # buttons
        fontRender = textFont.render("New",False,(255,255,255))
        pygame.draw.rect(display,(50,50,50),(410,300,100,25))
        display.blit(fontRender,(410,300))
        fontRender = textFont.render("Load",False,(255,255,255))
        pygame.draw.rect(display,(50,50,50),(290,300,100,25))
        display.blit(fontRender,(290,300))
        if(mousePosition[0]>410 and mousePosition[0]<510 and mousePosition[1]>300 and mousePosition[1]<325 and mouseClicked):
            editing = True
        elif(mousePosition[0]>290 and mousePosition[0]<390 and mousePosition[1]>300 and mousePosition[1]<325 and mouseClicked):
            open_file()
            editing = True
    else:
        x=0
        for tabs in ["textures","levels","settings"]:
            fontRender = textFont.render(tabs,False,(255,255,255))
            pygame.draw.rect(display,(50,50,50),(x,0,125,25))
            display.blit(fontRender,(x,0))
            if(mousePosition[0]>x and mousePosition[0]<x+125 and mousePosition[1]>0 and mousePosition[1]<25 and mouseClicked):
                tab = tabs
            x+=135
        if(tab == "textures"):
            y=65
            i=0
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
            pass
        elif(tab == "settings"):
            pass
    pygame.display.flip()
pygame.quit()