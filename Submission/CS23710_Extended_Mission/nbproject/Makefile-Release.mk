#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=cc
CCC=CC
CXX=CC
FC=f95
AS=as

# Macros
CND_PLATFORM=OracleSolarisStudio-Solaris-Sparc
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/loader.o \
	${OBJECTDIR}/course.o \
	${OBJECTDIR}/competitors.o \
	${OBJECTDIR}/nodes.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/event.o \
	${OBJECTDIR}/tracks.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cs23710_extended_mission

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cs23710_extended_mission: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cs23710_extended_mission ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/loader.o: loader.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -fast -g -o ${OBJECTDIR}/loader.o loader.c

${OBJECTDIR}/course.o: course.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -fast -g -o ${OBJECTDIR}/course.o course.c

${OBJECTDIR}/competitors.o: competitors.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -fast -g -o ${OBJECTDIR}/competitors.o competitors.c

${OBJECTDIR}/nodes.o: nodes.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -fast -g -o ${OBJECTDIR}/nodes.o nodes.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -fast -g -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/event.o: event.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -fast -g -o ${OBJECTDIR}/event.o event.c

${OBJECTDIR}/tracks.o: tracks.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -fast -g -o ${OBJECTDIR}/tracks.o tracks.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cs23710_extended_mission

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
