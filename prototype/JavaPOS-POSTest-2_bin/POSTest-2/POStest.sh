#!/bin/sh
CLASSPATH=postest2.jar
CLASSPATH=$CLASSPATH:jpos-1.13.0.jar
CLASSPATH=$CLASSPATH:xerces.jar
CLASSPATH=$CLASSPATH:.

REQUIRED_VERSION=1.7

# Transform the required version string into a number that can be used in comparisons
REQUIRED_VERSION=`echo $REQUIRED_VERSION | sed -e 's;\.;0;g'`
# Check JAVA_HOME directory to see if Java version is adequate
if [ $JAVA_HOME ]
then
	JAVA_EXE=$JAVA_HOME/bin/java
	$JAVA_EXE -version 2> tmp.ver
	VERSION=`cat tmp.ver | grep "java version" | awk '{ print substr($3, 2, length($3)-2); }'`
	rm tmp.ver
	VERSION=`echo $VERSION | awk '{ print substr($1, 1, 3); }' | sed -e 's;\.;0;g'`
	if [ $VERSION ]
	then
		if [ $VERSION -ge $REQUIRED_VERSION ]
		then
			JAVA_HOME=`echo $JAVA_EXE | awk '{ print substr($1, 1, length($1)-9); }'`
		else
			JAVA_HOME=
		fi
	else
		JAVA_HOME=
	fi
fi

# If the existing JAVA_HOME directory is adequate, then leave it alone
# otherwise, use 'locate' to search for other possible java candidates and
# check their versions.
if [ $JAVA_HOME ]
then
	:
else
	for JAVA_EXE in `locate bin/java | grep java$ | xargs echo`
	do
		if [ $JAVA_HOME ] 
		then
			:
		else
			$JAVA_EXE -version 2> tmp.ver 1> /dev/null
			VERSION=`cat tmp.ver | grep "java version" | awk '{ print substr($3, 2, length($3)-2); }'`
			rm tmp.ver
			VERSION=`echo $VERSION | awk '{ print substr($1, 1, 3); }' | sed -e 's;\.;0;g'`
			if [ $VERSION ]
			then
				if [ $VERSION -ge $REQUIRED_VERSION ]
				then
					JAVA_HOME=`echo $JAVA_EXE | awk '{ print substr($1, 1, length($1)-9); }'`
				fi
			fi
		fi
	done
fi

# If the correct Java version is detected, then export the JAVA_HOME environment variable
if [ $JAVA_HOME ]
then
	export JAVA_HOME
	CLASSPATH=$CLASSPATH:$JAVA_HOME/jre/lib/jfxrt.jar
	
	LIB_PATH=$LD_LIBRARY_PATH
	########################################
	#                                      #
	#  Add Device Specific jar's here...   #
	#                                      #
	########################################

	#CLASSPATH=$CLASSPATH:/path_to_service.jar

java -cp $CLASSPATH -Djava.library.path=$LIB_PATH postest2.POSTest2
else
	echo No Existing value of JAVA_HOME is available!
fi




