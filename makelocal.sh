#!/bin/bash

############################################################
# makelocal  - makefile模板库工具
# copyright by calvin 2013
# calvinwilliams.c@gmail.com
#
# 由最小makefile文件本地化展开或指定目标系统宏展开成可独立使用makefile
# 语法 : makelocal.sh [ OS ]
# 备注 : OS可以是Linux、AIX等支持环境，或指定all生成所有环境makefile
#        或不指定OS，工具自取环境变量MKTPL2_OS
############################################################

EXPAND_TABLE=""

ExpandMacro()
{
	local INFILE=$1
	local MACRO=$2
	local OUTFILE=$3
	local MACROBAK=""
	
	echo $EXPAND_TABLE | grep -w $MACRO > /dev/null
	R=$?
	if [ $R -eq 0 ] ; then
		return
	else
		EXPAND_TABLE="${EXPAND_TABLE} ${MACRO}"
	fi
	
	LINENUMBER=`grep -E -w -n "^\#\+ ${MACRO}" "${INFILE}" | awk -F: '{print $1}'`
	if [ $? -ne 0 -o "$LINENUMBER" -le 0 ] ; then
		return
	fi
	
	LINES=1
	IN_EXPAND_SECTION=0
	while read -r LINE2 ; do
		if [ $IN_EXPAND_SECTION -eq 0 ] ; then
			if [ $LINES -eq $LINENUMBER ] ; then
				IN_EXPAND_SECTION=1
				continue
			fi
			
			LINES=`expr $LINES + 1`
			continue
		fi
		
		FIELD1=`echo $LINE2 | awk '{print $1}'`
		FIELD2=`echo $LINE2 | awk '{print $2}'`
		
		if [ x"$FIELD1" = x"#@" ] ; then
			MACROBAK=$MACRO
			ExpandMacro "$INFILE" "$FIELD2" "$OUTFILE"
			echo ""
			MACRO=$MACROBAK
		elif [ x"$FIELD1" = x"#-" -a x"$FIELD2" = x"$MACRO" ] ; then
			break
		else
			echo "$LINE2"
		fi
	done < $INFILE >> $OUTFILE
}

OS=$1

if [ ! -f makefile ] ; then
	echo "makefile不存在"
	exit 0
fi

if [ x"$OS" = x"" ] ; then
	OS=${MKTPL2_OS}
elif [ x"$OS" = x"all" ] ; then
	OS='*'
fi

grep "include \${MKTPL2_HOME}/makeobj_\${MKTPL2_OS}.inc" makefile > /dev/null
if [ $? -eq 0 ] ; then
	OBJ_OR_DIR="obj"
else
	grep "include \${MKTPL2_HOME}/makedir_\${MKTPL2_OS}.inc" makefile > /dev/null
	if [ $? -eq 0 ] ; then
		OBJ_OR_DIR="dir"
	fi
fi

for FILE in `ls ${MKTPL2_HOME}/make${OBJ_OR_DIR}_${OS}.inc` ; do
	OS=`basename $FILE | tr '_.' '  ' | awk '{print $2}'`
	
	EXPAND_TABLE=""
	
	printf "# 此文件由makelocal.sh自动生成\n" > makefile.${OS}
	if [ x"${OS}" = x"*" ] ; then
		MAKEFILE_POSTFIX=""
	else
		MAKEFILE_POSTFIX=".${OS}"
	fi
	printf "MAKEFILE_POSTFIX=$MAKEFILE_POSTFIX\n" >> makefile.${OS}
	
	IFS=
	while read -r LINE1 ; do
		FIELD1=`echo $LINE1 | awk '{print $1}'`
		FIELD2=`echo $LINE1 | awk '{print $2}'`
		if [ x"$LINE1" = x"include \${MKTPL2_HOME}/make${OBJ_OR_DIR}_\${MKTPL2_OS}.inc" ] ; then
			continue
		elif [ x"$FIELD1" = x"#@" ] ; then
			ExpandMacro "$FILE" "$FIELD2" "makefile.${OS}"
			echo ""
		else
			echo $LINE1
		fi
	done < makefile >> makefile.${OS}
	unset IFS
done

