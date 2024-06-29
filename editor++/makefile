#================== SETTINGS ==================#
BUILD := ../build
OUT := ../bin
JAVAC := javac
#================== COMPILE ===================#
#	compiles editor++
all: build
#	for debugging SRCE's editor++
debug: build run clean
#	cleans up after building
clean:
	rm -r $(BUILD) -f
	rm -r $(OUT) -f
prep:
	mkdir -p $(BUILD)
	mkdir -p $(OUT)
compile:
	cd ../; javac -d ./editor++/$(BUILD) ./editor++/*.java
	cp manifest.mf $(BUILD)/manifest.mf
	cd $(BUILD); jar cfm $(OUT)/SRCEedit++.jar manifest.mf .
run:
	java -jar $(OUT)/SRCEedit++.jar
build: clean prep compile