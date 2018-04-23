#!/bin/sh

######################################################################
# makeobj - makefile模板库工具
# copyright by calvin 2013
# calvinwilliams.c@gmail.com
#
# 扫描源目录，自动生成基于mktpl模板库的最小化makefile雏形
# 语法 : makeobj.sh [ TARGET ]
# 备注 : TARGET可以是可执行文件或静态库(.a)或动态库(.so)
######################################################################

TARGET=$1
echo $TARGET | grep "." > /dev/null
if [ $? -eq 0 ] ; then
	TARGET_EXT=`echo $TARGET | awk -F. '{print $2}'`
fi

if [ -f makefile ] ; then
	echo "makefile已存在"
	exit 0
fi
if [ -f makeinstall ] ; then
	echo "makeinstall已存在"
	exit 0
fi

printf "# 此文件由makeobj.sh自动生成\n" > makefile

IFS=

_FILE_o=""
_INST=""
_UNINST=""
BLANKLING_FLAG=0

while read -r LINE ; do
	echo $LINE | grep -E "^[_a-zA-Z]*_FILE[\t]*" > /dev/null
	if [ $? -eq 0 ] ; then
		EXT=`echo $LINE | sed 's/_FILE/ /g' | awk '{print $1}'`
		if [ x"$EXT" != x"" ] ; then
			ls -d *.$EXT > /dev/null 2>&1
			if [ $? -eq 0 ] ; then
				printf "#@ ${EXT}_FILE\n"
				printf "$LINE\t\\\\\n"
				unset IFS
				for FILE in `ls *.$EXT` ; do
					printf "\t\t\t$FILE \\\\\n"
				done
				IFS=
				echo ; BLANKLING_FLAG=1
				if [ x"$_FILE_o" = x"" ] ; then
					_FILE_o="\$(${EXT}_FILE_o)"
				else
					_FILE_o="${_FILE_o} \$(${EXT}_FILE_o)"
				fi
				export _FILE_o
			fi
			continue
		fi
		continue
	fi
	
	FIELD1=`echo $LINE | awk '{print $1}'`
	
	if [ x"$FIELD1" = x"BIN" ] ; then
		if [ x"$TARGET" != "" ] ; then
			if [ x"$TARGET_EXT" = x"" -o x"$TARGET_EXT" = x"exe" ] ; then
				printf "BIN		=	$TARGET\n"
			fi
		fi
		continue
	elif [ x"$FIELD1" = x"BININST" ] ; then
		if [ x"$TARGET" != "" ] ; then
			if [ x"$TARGET_EXT" = x"" ] ; then
				printf "BININST		=	\$(_BININST)\n"
				_INST="${_INST}#@ make_install_BININST\n"
				_UNINST="${_UNINST}#@ make_uninstall_BININST\n"
			fi
		fi
		continue
	elif [ x"$FIELD1" = x"LIB" ] ; then
		if [ x"$TARGET" != "" ] ; then
			if [ x"$TARGET_EXT" = x"a" -o x"$TARGET_EXT" = x"so" ] ; then
				printf "LIB		=	$TARGET\n"
			fi
		fi
		continue
	elif [ x"$FIELD1" = x"LIBINST" ] ; then
		if [ x"$TARGET" != "" ] ; then
			if [ x"$TARGET_EXT" = x"a" -o x"$TARGET_EXT" = x"so" ] ; then
				printf "LIBINST		=	\$(_LIBINST)\n"
				_INST="${_INST}#@ make_install_LIBINST\n"
				_UNINST="${_UNINST}#@ make_uninstall_LIBINST\n"
			fi
		fi
		continue
	elif [ x"$FIELD1" = x"HDER" ] ; then
		ls -d *.h > /dev/null 2>&1
		if [ $? -eq 0 ] ; then
			printf "$LINE \\\\\n"
			unset IFS
			for FILE in `ls -d *.h` ; do
				printf "\t\t\t$FILE \\\\\n"
			done
			IFS=
			echo ; BLANKLING_FLAG=1
		fi
		continue
	elif [ x"$FIELD1" = x"HDERINST" ] ; then
		ls -d *.h > /dev/null 2>&1
		if [ $? -eq 0 ] ; then
			printf "$LINE	\$(_HDERINST)\n"
			_INST="${_INST}#@ make_install_HDERINST\n"
			_UNINST="${_UNINST}#@ make_uninstall_HDERINST\n"
			echo ; BLANKLING_FLAG=1
		fi
		continue
	elif [ x"$FIELD1" = x"DFTHDERINST" ] ; then
		_INST="${_INST}#@ make_install_DFTHDERINST\n"
		_UNINST="${_UNINST}#@ make_uninstall_DFTHDERINST\n"
		continue
	elif [ x"$FIELD1" = x"OBJ" ] ; then
		continue
	elif [ x"$FIELD1" = x"OBJINST" ] ; then
		continue
	elif [ x"$FIELD1" = x"NOCLEAN_OBJ" ] ; then
		continue
	elif [ x"$FIELD1" = x"NOCLEAN_OBJINST" ] ; then
		continue
	elif [ x"$FIELD1" = x"NOINST_OBJ" ] ; then
		continue
	elif [ x"$LINE" = x"include \${MKTPL2_HOME}/makeobj_\${MKTPL2_OS}.inc" ] ; then
		printf "#@ make_all\n"
		printf "#@ make_clean\n"
		printf "#@ make_install\n"
		if [ x"$_INST" != x"" ] ; then
			printf "${_INST}"
		fi
		printf "#@ make_uninstall\n"
		if [ x"$_UNINST" != x"" ] ; then
			printf "${_UNINST}"
		fi
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
done < ${MKTPL2_HOME}/makeobj.template >> makefile
unset IFS

if [ x"$TARGET" != "" ] ; then
	if [ x"$TARGET_EXT" = x"" ] ; then
		printf "$TARGET		:	${_FILE_o}\n" >> makefile
		printf "	\$(CC) -o \$@ ${_FILE_o} \$(LFLAGS)\n" >> makefile
	fi
	if [ x"$TARGET_EXT" = x"a" ] ; then
		printf "$TARGET		:	${_FILE_o}\n" >> makefile
		printf "	\$(AR) \$(ARFLAGS) \$@ ${_FILE_o}\n" >> makefile
	fi
	if [ x"$TARGET_EXT" = x"so" ] ; then
		printf "$TARGET		:	${_FILE_o}\n" >> makefile
		printf "	\$(CC) -o \$@ ${_FILE_o} \$(SOFLAGS) \$(LFLAGS)\n" >> makefile
	fi
fi

echo "" >> makefile

cp ${MKTPL2_HOME}/makeinstall.template makeinstall

