##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=backupd
ConfigurationName      :=Debug
WorkspacePath          := "/home/mgohde/codeliteworkspace"
ProjectPath            := "/home/mgohde/codeliteworkspace/backupd"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=mgohde
Date                   :=02/02/17
CodeLitePath           :="/home/mgohde/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="backupd.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)dl $(LibrarySwitch)pthread 
ArLibs                 :=  "dl" "pthread" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/utils.c$(ObjectSuffix) $(IntermediateDirectory)/daemon.c$(ObjectSuffix) $(IntermediateDirectory)/serverconfig.c$(ObjectSuffix) $(IntermediateDirectory)/plugins.c$(ObjectSuffix) $(IntermediateDirectory)/worker.c$(ObjectSuffix) $(IntermediateDirectory)/backupconfig.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/mgohde/codeliteworkspace/backupd/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/utils.c$(ObjectSuffix): utils.c $(IntermediateDirectory)/utils.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/mgohde/codeliteworkspace/backupd/utils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utils.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utils.c$(DependSuffix): utils.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utils.c$(ObjectSuffix) -MF$(IntermediateDirectory)/utils.c$(DependSuffix) -MM "utils.c"

$(IntermediateDirectory)/utils.c$(PreprocessSuffix): utils.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utils.c$(PreprocessSuffix) "utils.c"

$(IntermediateDirectory)/daemon.c$(ObjectSuffix): daemon.c $(IntermediateDirectory)/daemon.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/mgohde/codeliteworkspace/backupd/daemon.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/daemon.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/daemon.c$(DependSuffix): daemon.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/daemon.c$(ObjectSuffix) -MF$(IntermediateDirectory)/daemon.c$(DependSuffix) -MM "daemon.c"

$(IntermediateDirectory)/daemon.c$(PreprocessSuffix): daemon.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/daemon.c$(PreprocessSuffix) "daemon.c"

$(IntermediateDirectory)/serverconfig.c$(ObjectSuffix): serverconfig.c $(IntermediateDirectory)/serverconfig.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/mgohde/codeliteworkspace/backupd/serverconfig.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/serverconfig.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/serverconfig.c$(DependSuffix): serverconfig.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/serverconfig.c$(ObjectSuffix) -MF$(IntermediateDirectory)/serverconfig.c$(DependSuffix) -MM "serverconfig.c"

$(IntermediateDirectory)/serverconfig.c$(PreprocessSuffix): serverconfig.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/serverconfig.c$(PreprocessSuffix) "serverconfig.c"

$(IntermediateDirectory)/plugins.c$(ObjectSuffix): plugins.c $(IntermediateDirectory)/plugins.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/mgohde/codeliteworkspace/backupd/plugins.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/plugins.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/plugins.c$(DependSuffix): plugins.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/plugins.c$(ObjectSuffix) -MF$(IntermediateDirectory)/plugins.c$(DependSuffix) -MM "plugins.c"

$(IntermediateDirectory)/plugins.c$(PreprocessSuffix): plugins.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/plugins.c$(PreprocessSuffix) "plugins.c"

$(IntermediateDirectory)/worker.c$(ObjectSuffix): worker.c $(IntermediateDirectory)/worker.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/mgohde/codeliteworkspace/backupd/worker.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/worker.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/worker.c$(DependSuffix): worker.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/worker.c$(ObjectSuffix) -MF$(IntermediateDirectory)/worker.c$(DependSuffix) -MM "worker.c"

$(IntermediateDirectory)/worker.c$(PreprocessSuffix): worker.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/worker.c$(PreprocessSuffix) "worker.c"

$(IntermediateDirectory)/backupconfig.c$(ObjectSuffix): backupconfig.c $(IntermediateDirectory)/backupconfig.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/mgohde/codeliteworkspace/backupd/backupconfig.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/backupconfig.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/backupconfig.c$(DependSuffix): backupconfig.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/backupconfig.c$(ObjectSuffix) -MF$(IntermediateDirectory)/backupconfig.c$(DependSuffix) -MM "backupconfig.c"

$(IntermediateDirectory)/backupconfig.c$(PreprocessSuffix): backupconfig.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/backupconfig.c$(PreprocessSuffix) "backupconfig.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


