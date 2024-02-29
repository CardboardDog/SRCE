#================== SETTINGS ==================#
#	Windows Settings
WCC = gcc
WCARG = -lmingw32 -lSDL2main -lSDL2
#	Linux 
LCC = wsl gcc
LCARG = -lSDL2 -lm
#	universal
ENTRY = Main
OUT = ../bin
DEMO = demo
DOUT = C:/SRCE/
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
	if [ -d $(DOUT) ]; then \
		rm $(DOUT)/*; \
		rmdir $(DOUT)/; \
		mkdir $(DOUT)/; \
	else \
		mkdir $(DOUT)/; \
	fi;
windows:
	echo "Building for Windows..."
	$(WCC) $(ENTRY).c -o $(OUT)/$(ENTRY).exe $(WCARG)
	cp ../game/$(DEMO).eyn $(DOUT)/$(DEMO).eyn
linux:
	echo "Building for Linux/RPI..."
	$(LCC) $(ENTRY).c -o $(OUT)/$(ENTRY) $(LCARG)