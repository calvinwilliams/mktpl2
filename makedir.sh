#!/bin/sh

############################################################
# makedir v2.0.0 - makefile模板库工具
# copyright by calvin 2013
# calvinwilliams.c@gmail.com
#
# 扫描子目录列表，自动生成基于mktpl模板库的最小化makefile雏形
# 语法 : makedir.sh
############################################################

BLANKLING_FLAG=0

TARGET=$1

if [ -f makefile ] ; then
	echo "makefile已存在"
	exit 0
fi

printf "# 此文件由makedir.sh自动生成\n" > makefile

while read LINE ; do
	FIELD1=`echo $LINE | awk '{print $1}'`
	
	if [ x"$FIELD1" = x"DIROBJS" ] ; then
		printf "$LINE \\\\\n"
		for FILE in `ls -l | grep -E "^d" | awk '{print $NF}'` ; do
			
			printf "\t\t\t$FILE \\\\\n"
		done
		echo ; BLANKLING_FLAG=1
		continue
	elif [ x"$LINE" = x"include \$(MKTPLDIR)/makedir_\$(MKTPLOS).inc" ] ; then
		printf "#@ FILESYSTEM\n"
		printf "#@ dir_all\n"
		printf "#@ dir_make\n"
		printf "#@ dir_clean\n"
		printf "#@ dir_install\n"
		printf "#@ dir_uninstall\n"
	fi
	
	if [ x"$LINE" = x"" ] ; then
		if [ $BLANKLING_FLAG -ne 1 ] ; then
			echo $LINE
			BLANKLING_FLAG=1
		fi
	else
		echo $LINE
		BLANKLING_FLAG=0
	fi
done < ${MKTPLDIR}/makedir.template >> makefile

echo "" >> makefile
