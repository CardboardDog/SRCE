import regex
palette = [[0,0,0],[127,127,127],[136,0,21],[237,28,36],[255,127,39],[255,242,0],[34,177,76],[0,162,232],[63,72,204],[163,73,164],[255,255,255],[195,195,195],[185,122,87],[255,174,201],[255,201,14],[239,228,176],[181,230,29],[153,217,234],[112,146,190],[200,255,231]]
def char_to_int(character):
    if(character.isdigit()):
        return int(character, 16);
    else:
        return abs(ord(character)-55);
def load_texture_pixel(file, level, x, y):
    gameFile = open(file,'r')
    settingsOpen = 0
    scanY = 0
    beginLevelName = "NAME "+level+"\n"
    lines = gameFile.readlines()
    for charBuffer in lines:
        if(charBuffer=="GMTEX:\n"):
            settingsOpen = 1
        if(settingsOpen==1 and charBuffer==beginLevelName):
            settingsOpen = 2
        if(settingsOpen==2 and charBuffer=="TEXBF:\n"):
            settingsOpen = 3
            scanY = 0
        elif(settingsOpen==3):
            if(charBuffer=="END\n"):
                break
            if(scanY==y):
                gameFile.close()
                return char_to_int(charBuffer[x])
            scanY+=1
    gameFile.close()
    return 0
def load_texture(file, texture):
    textureBuffer = [[0 for x in range(64)] for y in range(64)] 
    for y in range(64):
        for x in range(64):
            textureBuffer[x][y]=load_texture_pixel(file,texture,x,y)
    return textureBuffer
def read_file_textures(file):
    fileReader = open(file,'r')
    fileText = fileReader.read()
    fileReader.close()
    fileGroups = regex.findall(r'GMTEX:\nNAME (.*)\n',fileText)
    textureDict = {}
    for i in fileGroups:
        textureDict[i] = load_texture(file,i)   
    return textureDict
def load_level_pixel(file, level, x, y):
    gameFile = open(file,'r')
    settingsOpen = 0
    scanY = 0
    beginLevelName = "NAME "+level+"\n"
    lines = gameFile.readlines()
    for charBuffer in lines:
        if(charBuffer=="LBFER:\n"):
            settingsOpen = 1
        if(settingsOpen==1 and charBuffer==beginLevelName):
            settingsOpen = 2
        if(settingsOpen==2 and charBuffer=="LWALL:\n"):
            settingsOpen = 3
            scanY = 0
        elif(settingsOpen==3):
            if(charBuffer=="END\n"):
                break
            if(scanY==y):
                gameFile.close()
                return char_to_int(charBuffer[x])
            scanY+=1
    gameFile.close()
    return 0
def load_level(file, level, scale):
    textureBuffer = [[0 for x in range(scale[0])] for y in range(scale[1])] 
    for y in range(scale[1]):
        for x in range(scale[0]):
            textureBuffer[x][y]=load_level_pixel(file,level,x,y)
    return textureBuffer
def load_height_pixel(file, level, x, y):
    gameFile = open(file,'r')
    settingsOpen = 0
    scanY = 0
    beginLevelName = "NAME "+level+"\n"
    lines = gameFile.readlines()
    for charBuffer in lines:
        if(charBuffer=="LBFER:\n"):
            settingsOpen = 1
        if(settingsOpen==1 and charBuffer==beginLevelName):
            settingsOpen = 2
        if(settingsOpen==2 and charBuffer=="WHGHT:\n"):
            settingsOpen = 3
            scanY = 0
        elif(settingsOpen==3):
            if(charBuffer=="END\n"):
                break
            if(scanY==y):
                gameFile.close()
                return char_to_int(charBuffer[x])
            scanY+=1
    gameFile.close()
    return 0
def load_height(file, level, scale):
    textureBuffer = [[0 for x in range(scale[0])] for y in range(scale[1])] 
    for y in range(scale[1]):
        for x in range(scale[0]):
            textureBuffer[x][y]=load_height_pixel(file,level,x,y)
    return textureBuffer
def load_level_size(file, name):
    fileReader = open(file,'r')
    fileText = fileReader.read()
    fileReader.close()
    pSet = regex.findall(r'LBFER:\nNAME '+name+r'\nXSTRT (.*)\nYSTRT (.*)',fileText)
    sSet = regex.findall(r'SMODE:\nLWDTH (.*)\nLHGHT (.*)',fileText)
    return (int(pSet[0][0]),int(pSet[0][1]),int(sSet[0][0]),int(sSet[0][1]))
def read_file_levels(file):
    fileReader = open(file,'r')
    fileText = fileReader.read()
    fileReader.close()
    fileGroups = regex.findall(r'LBFER:\nNAME (.*)\n',fileText)
    textureDict = {}
    for i in fileGroups:
        levelInfo = load_level_size(file,i)
        tupleSet = (levelInfo,load_level(file,i,(levelInfo[2],levelInfo[3])),load_height(file,i,(levelInfo[2],levelInfo[3])))
        textureDict[i] = tupleSet
    return textureDict