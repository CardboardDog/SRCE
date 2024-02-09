#================== SETTINGS ==================#
#	Windows Settings
WCC = gcc
WCARG = -lmingw32 -lSDL2main -lSDL2
#	Linux 
LCC = wsl gcc
LCARG = -lSDL2
#	universal
ENTRY = Main
OUT = ../bin

#================== COMPILE ===================#
# clean then build for all platforms 
all: clean windows linux
clean:
	echo "Cleaning..."
	if [ -d $(OUT) ]; then \
		rm $(OUT)/*; \
		rmdir $(OUT)/; \
		mkdir $(OUT)/; \
	else \
		mkdir $(OUT)/; \
	fi;
	echo "Cleaned"
windows:
	echo "Building for Windows..."
	$(WCC) $(ENTRY).c -o $(OUT)/$(ENTRY).exe $(WCARG)
linux:
	echo "Building for Linux/RPI..."
	$(LCC) $(ENTRY).c -o $(OUT)/$(ENTRY) $(LCARG)