######################################################################
# mktpl - makefile模板库
# copyright by calvin 2013
# calvinwilliams.c@gmail.com
#
# 使用工具makeobj.sh、makedir.sh自动生成或编写最小化makefile
# ，装载公共规则库实现makefile
# 或 然后用工具makelocal.sh本地化展开生成独立makefile
######################################################################

#################### 操作系统环境本地化宏、公共宏 ####################

#+ FILESYSTEM
# 文件系统宏
CD		=	cd
RM		=	rm -f
CP		=	cp -f
MV		=	mv -f
MKDIR		=	mkdir -p
#- FILESYSTEM

#+ cx_FILE
# 编译宏
AR		=	ar
AFLAGS		=	rv
SOFLAGS		=	-shared
ESOFLAGS	=	
#- cx_FILE

#################### 所有最终目标列表 ####################

#+ make_all
# 最终目标列表
all	:	$(OBJ) $(OBJ2) $(LIB) $(LIB2) $(SQL) $(NOCLEAN_OBJ) $(NOINST_OBJ) $(BIN) $(BIN2)
#- make_all

#################### 预定义源文件类型宏、关联宏及推导规则 ####################

#+ c_FILE
#@ cx_FILE
# c源代码文件宏及推导规则
CC		=	gcc -g -fPIC -O2 -Wall -Werror -fno-strict-aliasing
CC_NOWARN	=	gcc -g -fPIC -O2

c_FILE_o	=	$(c_FILE:.c=.o)
c_FILE2_o	=	$(c_FILE2:.c=.o)
c_FILE3_o	=	$(c_FILE3:.c=.o)
c_FILE4_o	=	$(c_FILE4:.c=.o)
c_FILE5_o	=	$(c_FILE5:.c=.o)
c_FILE_CLEAN	=	$(c_FILE_o) $(c_FILE2_o) $(c_FILE3_o) $(c_FILE4_o) $(c_FILE5_o)

.SUFFIXES:.c
.c.o	:
	$(CC) $(CFLAGS) -c $<
#- c_FILE

#+ cpp_FILE
#@ cx_FILE
# c++源代码文件宏及推导规则
CPPC		=	g++ -g -fPIC -O2 -Wall -Werror -fno-strict-aliasing
CPPC_NOWARN	=	g++ -g -fPIC -O2

cpp_FILE_o	=	$(cpp_FILE:.cpp=.o)
cpp_FILE2_o	=	$(cpp_FILE2:.cpp=.o)
cpp_FILE3_o	=	$(cpp_FILE3:.cpp=.o)
cpp_FILE4_o	=	$(cpp_FILE4:.cpp=.o)
cpp_FILE5_o	=	$(cpp_FILE5:.cpp=.o)
cpp_FILE_CLEAN	=	$(cpp_FILE_o) $(cpp_FILE2_o) $(cpp_FILE3_o) $(cpp_FILE4_o) $(cpp_FILE5_o)

.SUFFIXES:.cpp
.cpp.o	:
	$(CPPC) $(CFLAGS) -c $<
#- cpp_FILE

#+ SQC_FILE
#@ c_FILE
# ESQL源代码文件宏及推导规则
SQCP		=	proc

SQC_FILE_sqec	=	$(SQC_FILE:.SQC=.sqec)
SQC_FILE_c	=	$(SQC_FILE:.SQC=.c)
SQC_FILE_o	=	$(SQC_FILE:.SQC=.o)
SQC_FILE_CLEAN	=	$(SQC_FILE_sqec) $(SQC_FILE_c) $(SQC_FILE_o)

.SUFFIXES:.SQC
.SQC.c	:
	$(CC) -E $(CFLAGS) -x c $*.SQC > $*.sqec
	$(SQCP) $*.sqec parse=none
#- SQC_FILE

#+ ec_FILE
#@ c_FILE
# ESQL源代码文件宏及推导规则
# ECP		=	proc
ECP		=	ecpg

ec_FILE_sqec	=	$(ec_FILE:.ec=.sqec)
ec_FILE_c	=	$(ec_FILE:.ec=.c)
ec_FILE_o	=	$(ec_FILE:.ec=.o)
ec_FILE_CLEAN	=	$(ec_FILE_sqec) $(ec_FILE_c) $(ec_FILE_o)

.SUFFIXES:.ec
.ec.c	:
	$(CC) -E $(CFLAGS) -x c $*.ec > $*.sqec
	$(ECP) $*.sqec
#- ec_FILE

#+ csm_FILE
#@ c_FILE
# 数据字典定义文件宏及推导规则
CSM			=	csm

csm_FILE_h		=	$(csm_FILE:.csm=.h)
csm_FILE_c		=	$(csm_FILE:.csm=.c)
csm_FILE_DUMP_c		=	$(csm_FILE:.csm=.DUMP.c)
csm_FILE_MAP_c		=	$(csm_FILE:.csm=.MAP.c)
csm_FILE_LOG_c		=	$(csm_FILE:.csm=.LOG.c)
csm_FILE_CLOG_c		=	$(csm_FILE:.csm=.CLOG.c)
csm_FILE_o		=	$(csm_FILE:.csm=.o)
csm_FILE_CLEAN		=	$(csm_FILE_h) $(csm_FILE_c) $(csm_FILE_DUMP_c) $(csm_FILE_MAP_c) $(csm_FILE_LOG_c) $(csm_FILE_CLOG_c) $(csm_FILE_o)
csm_FILE_DFTHDER	=	$(csm_FILE_h) $(csm_FILE_LOG_c) $(csm_FILE_CLOG_c)

.SUFFIXES:.csm
.csm.c	:
	$(CSM) $<
#- csm_FILE

#+ c_html_FILE
#@ c_FILE
# CSP源代码文件宏及推导规则
CSPP			=	cspp

c_html_FILE_c		=	$(c_html_FILE:.c.html=.c)
c_html_FILE_o		=	$(c_html_FILE:.c.html=.o)
c_html_FILE_CLEAN	=	$(c_html_FILE_c) $(c_html_FILE_o)

%.c	:	%.c.html
	$(CSPP) $*.c.html > $*.c
#- c_html_FILE

#+ cui_FILE
#@ c_FILE
# CUI定义文件宏及推导规则
CUIP			=	cuip

cui_FILE_h		=	$(cui_FILE:.cui=.h)
cui_FILE_STRUCT_h	=	$(cui_FILE:.cui=.STRUCT.h)
cui_FILE_WINDMAP_h	=	$(cui_FILE:.cui=.WINDMAP.h)
cui_FILE_WINMAIN_h	=	$(cui_FILE:.cui=.WINMAIN.h)
cui_FILE_WINPROC_h	=	$(cui_FILE:.cui=.WINPROC.h)
cui_FILE_c		=	$(cui_FILE:.cui=.c)
cui_FILE_WINDMAP_c	=	$(cui_FILE:.cui=.WINDMAP.c)
cui_FILE_WINMAIN_c	=	$(cui_FILE:.cui=.WINMAIN.c)
cui_FILE_WINPROC_c	=	$(cui_FILE:.cui=.WINPROC.c)
cui_FILE_o		=	$(cui_FILE:.cui=.o)
cui_FILE_CLEAN		=	$(cui_FILE_h) $(cui_FILE_STRUCT_h) $(cui_FILE_WINDMAP_h) $(cui_FILE_WINMAIN_h) $(cui_FILE_WINPROC_h)
cui_FILE_DFTHDER	=	$(cui_FILE_h) $(cui_FILE_STRUCT_h) $(cui_FILE_WINDMAP_h) $(cui_FILE_WINMAIN_h) $(cui_FILE_WINPROC_h)

.SUFFIXES:.cui
.cui.c	:
	$(CUIP) $<
#- cui_FILE

#+ dtd_FILE
#@ c_FILE
# 数据库表结构定义文件宏及推导规则
DTDP			=	dtd

dtd_FILE_h		=	$(dtd_FILE:.dtd=.h)
dtd_FILE_SQLDECLARE_h	=	$(dtd_FILE:.dtd=.SQLDECLARE.h)
dtd_FILE_struct_h	=	$(dtd_FILE:.dtd=.struct.h)
dtd_FILE_TFLIST_h	=	$(dtd_FILE:.dtd=.TFLIST.h)
dtd_FILE_DBVLIST_h	=	$(dtd_FILE:.dtd=.DBVLIST.h)
dtd_FILE_DBVLLIST_h	=	$(dtd_FILE:.dtd=.DBVLLIST.h)
dtd_FILE_cnddef_ch	=	$(dtd_FILE:.dtd=.cndef.ch)
dtd_FILE_cnddef_h	=	$(dtd_FILE:.dtd=.cndef.h)
dtd_FILE_SQC		=	$(dtd_FILE:.dtd=.SQC)
dtd_FILE_DECLARE_SQC	=	$(dtd_FILE:.dtd=.SQLDECLARE.SQC)
dtd_FILE_DTDINIT_SQC	=	$(dtd_FILE:.dtd=.DTDINIT.SQC)
dtd_FILE_DTDVTOS_SQC	=	$(dtd_FILE:.dtd=.DTDVTOS.SQC)
dtd_FILE_DTDSTOV_SQC	=	$(dtd_FILE:.dtd=.DTDSTOV.SQC)
dtd_FILE_create_sql	=	$(dtd_FILE:.dtd=.create.sql)
dtd_FILE_drop_sql	=	$(dtd_FILE:.dtd=.drop.sql)
dtd_FILE_sqec		=	$(dtd_FILE:.dtd=.sqec)
dtd_FILE_c		=	$(dtd_FILE:.dtd=.c)
dtd_FILE_o		=	$(dtd_FILE:.dtd=.o)
dtd_FILE_DTDLOG_c	=	$(dtd_FILE:.dtd=.DTDLOG.c)
dtd_FILE_DTDCLOG_c	=	$(dtd_FILE:.dtd=.DTDCLOG.c)
dtd_FILE_env		=	$(dtd_FILE:.dtd=.env)
dtd_FILE_def_h		=	$(dtd_FILE:.dtd=.def.h)
dtd_FILE_DTDTRIM_c	=	$(dtd_FILE:.dtd=.DTDTRIM.c)
dtd_FILE_DTDACTION_h	=	$(dtd_FILE:.dtd=.DTDACTION.h)
dtd_FILE_DTDACTION_SQC	=	$(dtd_FILE:.dtd=.DTDACTION.SQC)
dtd_FILE_DTDACTION_sqec	=	$(dtd_FILE:.dtd=.DTDACTION.sqec)
dtd_FILE_DTDACTION_c	=	$(dtd_FILE:.dtd=.DTDACTION.c)
dtd_FILE_DTDACTION_o	=	$(dtd_FILE:.dtd=.DTDACTION.o)
dtd_FILE_CLEAN		=	$(dtd_FILE_h) $(dtd_FILE_SQLDECLARE_h) $(dtd_FILE_struct_h) $(dtd_FILE_TFLIST_h) $(dtd_FILE_DBVLIST_h) $(dtd_FILE_DBVLLIST_h) $(dtd_FILE_cnddef_ch) $(dtd_FILE_cnddef_h) $(dtd_FILE_SQC) $(dtd_FILE_DECLARE_SQC) $(dtd_FILE_DTDINIT_SQC) $(dtd_FILE_DTDVTOS_SQC) $(dtd_FILE_DTDSTOV_SQC) $(dtd_FILE_create_sql) $(dtd_FILE_drop_sql) $(dtd_FILE_sqec) $(dtd_FILE_c) $(dtd_FILE_DTDLOG_c) $(dtd_FILE_DTDCLOG_c) $(dtd_FILE_env) $(dtd_FILE_def_h) $(dtd_FILE_DTDTRIM_c) $(dtd_FILE_DTDACTION_h) $(dtd_FILE_DTDACTION_SQC) $(dtd_FILE_DTDACTION_sqec) $(dtd_FILE_DTDACTION_c) $(dtd_FILE_DTDACTION_o)
dtd_FILE_DFTHDER	=	$(dtd_FILE_h) $(dtd_FILE_SQLDECLARE_h) $(dtd_FILE_struct_h) $(dtd_FILE_TFLIST_h) $(dtd_FILE_DBVLIST_h) $(dtd_FILE_DBVLLIST_h) $(dtd_FILE_cnddef_h) $(dtd_FILE_def_h)

.SUFFIXES:.dtd
.dtd.c	:
	$(DTDP) $<
#- dtd_FILE

#+ prt_FILE
# 打印格式定义文件宏及推导规则
PRT2HP			=	prt2h

prt_FILE_h		=	$(prt_FILE:.prt=.h)
prt_FILE_CLEAN		=	$(prt_FILE_h)
prt_FILE_DFTHDER	=	$(prt_FILE_h)

.SUFFIXES:.prt
.prt.h	:
	$(PRT2HP) $<
#- prt_FILE

#+ fmd_FILE
#@ c_FILE
# 定长报文定义文件宏及推导规则
FMDP			=	fmd

fmd_FILE_h		=	$(fmd_FILE:.fmd=.h)
fmd_FILE_c		=	$(fmd_FILE:.fmd=.c)
fmd_FILE_COMPACK_c	=	$(fmd_FILE:.fmd=.COMPACK.c)
fmd_FILE_COMUNPACK_c	=	$(fmd_FILE:.fmd=.COMUNPACK.c)
fmd_FILE_COMLOG_c	=	$(fmd_FILE:.fmd=.COMLOG.c)
fmd_FILE_COMCLOG_c	=	$(fmd_FILE:.fmd=.COMCLOG.c)
fmd_FILE_COMTRIM_c	=	$(fmd_FILE:.fmd=.COMTRIM.c)
fmd_FILE_cndef_ch	=	$(fmd_FILE:.fmd=.cndef.ch)
fmd_FILE_cndef_h	=	$(fmd_FILE:.fmd=.cndef.h)
fmd_FILE_COMFLDLENDEF_h	=	$(fmd_FILE:.fmd=.COMFLDLENDEF.h)
fmd_FILE_COMOFFSETDEF_h	=	$(fmd_FILE:.fmd=.COMOFFSETDEF.h)
fmd_FILE_COMFLDMAP_c	=	$(fmd_FILE:.fmd=.COMFLDMAP.c)
fmd_FILE_o		=	$(fmd_FILE:.fmd=.o)
fmd_FILE_CLEAN		=	$(fmd_FILE_h) $(fmd_FILE_c) $(fmd_FILE_COMPACK_c) $(fmd_FILE_COMUNPACK_c) $(fmd_FILE_COMLOG_c) $(fmd_FILE_COMCLOG_c) $(fmd_FILE_COMTRIM_c) $(fmd_FILE_cndef_ch) $(fmd_FILE_cndef_h) $(fmd_FILE_COMFLDLENDEF_h) $(fmd_FILE_COMOFFSETDEF_h) $(fmd_FILE_COMFLDMAP_c) $(fmd_FILE_o)
fmd_FILE_DFTHDER	=	$(fmd_FILE_h) $(fmd_FILE_COMLOG_c) $(fmd_FILE_COMCLOG_c) $(fmd_FILE_COMFLDLENDEF_h) $(fmd_FILE_COMOFFSETDEF_h)

.SUFFIXES:.fmd
.fmd.c	:
	$(FMDP) $<
#- fmd_FILE

#+ smd_FILE
#@ c_FILE
# 分隔符报文定义文件宏及推导规则
SMDP			=	smd

smd_FILE_h		=	$(smd_FILE:.smd=.h)
smd_FILE_c		=	$(smd_FILE:.smd=.c)
smd_FILE_COMPACK_c	=	$(smd_FILE:.smd=.COMPACK.c)
smd_FILE_COMUNPACK_c	=	$(smd_FILE:.smd=.COMUNPACK.c)
smd_FILE_COMLOG_c	=	$(smd_FILE:.smd=.COMLOG.c)
smd_FILE_COMCLOG_c	=	$(smd_FILE:.smd=.COMCLOG.c)
smd_FILE_cndef_ch	=	$(smd_FILE:.smd=.cndef.ch)
smd_FILE_cndef_h	=	$(smd_FILE:.smd=.cndef.h)
smd_FILE_o		=	$(smd_FILE:.smd=.o)
smd_FILE_CLEAN		=	$(smd_FILE_h) $(smd_FILE_c) $(smd_FILE_COMPACK_c) $(smd_FILE_COMUNPACK_c) $(smd_FILE_COMLOG_c) $(smd_FILE_COMCLOG_c) $(smd_FILE_COMTRIM_c) $(smd_FILE_cndef_ch) $(smd_FILE_cndef_h) $(smd_FILE_o)
smd_FILE_DFTHDER	=	$(smd_FILE_h) $(smd_FILE_COMLOG_c) $(smd_FILE_COMCLOG_c)

.SUFFIXES:.smd
.smd.c	:
	$(SMDP) $<
#- smd_FILE

#+ def_FILE
#@ c_FILE
# IB1通讯结构定义文件宏及推导规则
DEFP			=	comAction

def_FILE_h		=	$(def_FILE:.def=.h)
def_FILE_c		=	$(def_FILE:.def=.c)
def_FILE_o		=	$(def_FILE:.def=.o)
def_FILE_CLEAN		=	$(def_FILE_h) $(def_FILE_c) $(def_FILE_o)
def_FILE_DFTHDER	=	$(def_FILE_h)

.SUFFIXES:.def
.def.c	:
	comAction ABRCP $<
#- def_FILE

#+ act_FILE
#@ c_FILE
# ACT定义文件宏及推导规则
ACTP			=	db8action

act_FILE_h		=	$(act_FILE:.act=.h)
act_FILE_c		=	$(act_FILE:.act=.c)
act_FILE_sql		=	$(act_FILE:.act=.sql)
act_FILE_o		=	$(act_FILE:.act=.o)
act_FILE_CLEAN		=	$(act_FILE_h) $(act_FILE_c) $(act_FILE_sql) $(act_FILE_o)
act_FILE_DFTHDER	=	$(act_FILE_h)

.SUFFIXES:.act
.act.c	:
	$(ACTP) DB $< -o
#- act_FILE

#+ sml2c_FILE
#@ c_FILE
# SML报文定义文件宏及推导规则
SML2C			=	sml2c

sml2c_FILE_h		=	$(sml2c_FILE:.sml2c=.h)
sml2c_FILE_SSDSTRUCT_h	=	$(sml2c_FILE:.sml2c=.SSDSTRUCT.h)
sml2c_FILE_c		=	$(sml2c_FILE:.sml2c=.c)
sml2c_FILE_SSDMAPPING_c	=	$(sml2c_FILE:.sml2c=.SSDMAPPING.c)
sml2c_FILE_SSDUNMAPPING_c=	$(sml2c_FILE:.sml2c=.SSDUNMAPPING.c)
sml2c_FILE_SSDTRIM_c	=	$(sml2c_FILE:.sml2c=.SSDTRIM.c)
sml2c_FILE_SSDFREE_c	=	$(sml2c_FILE:.sml2c=.SSDFREE.c)
sml2c_FILE_SSDLOG_c	=	$(sml2c_FILE:.sml2c=.SSDLOG.c)
sml2c_FILE_o		=	$(sml2c_FILE:.sml2c=.o)
sml2c_FILE_SSDLOG_o	=	$(sml2c_FILE:.sml2c=.SSDLOG.o)
sml2c_FILE_CLEAN	=	$(sml2c_FILE_h) $(sml2c_FILE_SSDSTRUCT_h) $(sml2c_FILE_c) $(sml2c_FILE_SSDMAPPING_c) $(sml2c_FILE_SSDUNMAPPING_c) $(sml2c_FILE_SSDTRIM_c) $(sml2c_FILE_SSDFREE_c) $(sml2c_FILE_SSDLOG_c) $(sml2c_FILE_o) $(sml2c_FILE_SSDLOG_o)
sml2c_FILE_DFTHDER	=	$(sml2c_FILE_h) $(sml2c_FILE_SSDSTRUCT_h) $(sml2c_FILE_SSDLOG_c)

.SUFFIXES:.sml2c
.sml2c.c	:
	$(SML2C) $<
#- sml2c_FILE

#################### clean清理删除规则 ####################

#+ make_clean
#@ FILESYSTEM
# 预定义源文件清理删除关联宏
_FILE_CLEAN	=	$(c_FILE_CLEAN) $(cpp_FILE_CLEAN) $(SQC_FILE_CLEAN) $(csm_FILE_CLEAN) $(c_html_FILE_CLEAN) $(cui_FILE_CLEAN) $(dtd_FILE_CLEAN) $(prt_FILE_CLEAN) $(fmd_FILE_CLEAN) $(smd_FILE_CLEAN) $(def_FILE_CLEAN) $(act_FILE_CLEAN) $(sml2c_FILE_CLEAN)

# 清理删除规则
.PHONY:clean
clean		:
	@for FILE in $(_FILE_CLEAN) $(BIN) $(BIN2) $(LIB) $(LIB2) $(OBJ) $(OBJ2) $(NOINST_OBJ) $(CLEAN_ADDITION) ; do \
		echo $(RM) $$FILE ; \
		$(RM) $$FILE ; \
	done
#- make_clean

#################### install提交安装规则 ####################

#+ make_install
#@ FILESYSTEM
# 预定义源代码缺省头文件宏
DFTHDER		=	$(csm_FILE_DFTHDER) $(cui_FILE_DFTHDER) $(dtd_FILE_DFTHDER) $(prt_FILE_DFTHDER) $(fmd_FILE_DFTHDER) $(smd_FILE_DFTHDER) $(def_FILE_DFTHDER) $(act_FILE_DFTHDER) $(sml2c_FILE_DFTHDER)

# 提交安装规则
.PHONY:install
install		:	all
#- make_install
#+ make_install_BININST
ifneq ($(strip $(BIN)),)
ifneq ($(strip $(BININST)),)
	@if [ ! -d "$(BININST)" ] ; then \
		echo $(MKDIR) $(BININST) ; \
		$(MKDIR) $(BININST) ; \
	fi ; \
	for FILE in `echo $(BIN)` ; do \
		echo $(CP) $$FILE $(BININST)/ ; \
		$(RM) $(BININST)/$$FILE ; \
		$(CP) $$FILE $(BININST)/ ; \
	done
endif
endif
#- make_install_BININST
#+ make_install_BININST2
ifneq ($(strip $(BIN2)),)
ifneq ($(strip $(BININST2)),)
	@if [ ! -d "$(BININST2)" ] ; then \
		echo $(MKDIR) $(BININST2) ; \
		$(MKDIR) $(BININST2) ; \
	fi ; \
	for FILE in `echo $(BIN2)` ; do \
		echo $(CP) $$FILE $(BININST2)/ ; \
		$(RM) $(BININST2)/$$FILE ; \
		$(CP) $$FILE $(BININST2)/ ; \
	done
endif
endif
#- make_install_BININST2
#+ make_install_LIBINST
ifneq ($(strip $(LIB)),)
ifneq ($(strip $(LIBINST)),)
	@if [ ! -d "$(LIBINST)" ] ; then \
		echo $(MKDIR) $(LIBINST) ; \
		$(MKDIR) $(LIBINST) ; \
	fi ; \
	for FILE in `echo $(LIB)` ; do \
		echo $(CP) $$FILE $(LIBINST)/ ; \
		$(RM) $(LIBINST)/$$FILE ; \
		$(CP) $$FILE $(LIBINST)/ ; \
	done
endif
endif
#- make_install_LIBINST
#+ make_install_LIBINST2
ifneq ($(strip $(LIB2)),)
ifneq ($(strip $(LIBINST2)),)
	@if [ ! -d "$(LIBINST2)" ] ; then \
		echo $(MKDIR) $(LIBINST2) ; \
		$(MKDIR) $(LIBINST2) ; \
	fi ; \
	for FILE in `echo $(LIB2)` ; do \
		echo $(CP) $$FILE $(LIBINST2)/ ; \
		$(RM) $(LIBINST2)/$$FILE ; \
		$(CP) $$FILE $(LIBINST2)/ ; \
	done
endif
endif
#- make_install_LIBINST2
#+ make_install_HDERINST
ifneq ($(strip $(HDER)),)
ifneq ($(strip $(HDERINST)),)
	@if [ ! -d "$(HDERINST)" ] ; then \
		echo $(MKDIR) $(HDERINST) ; \
		$(MKDIR) $(HDERINST) ; \
	fi ; \
	for FILE in `echo $(HDER)` ; do \
		echo $(CP) $$FILE $(HDERINST)/ ; \
		$(RM) $(HDERINST)/$$FILE ; \
		$(CP) $$FILE $(HDERINST)/ ; \
	done
endif
endif
#- make_install_HDERINST
#+ make_install_HDERINST2
ifneq ($(strip $(HDER2)),)
ifneq ($(strip $(HDERINST2)),)
	@if [ ! -d "$(HDERINST2)" ] ; then \
		echo $(MKDIR) $(HDERINST2) ; \
		$(MKDIR) $(HDERINST2) ; \
	fi ; \
	for FILE in `echo $(HDER2)` ; do \
		echo $(CP) $$FILE $(HDERINST2)/ ; \
		$(RM) $(HDERINST2)/$$FILE ; \
		$(CP) $$FILE $(HDERINST2)/ ; \
	done
endif
endif
#- make_install_HDERINST2
#+ make_install_DFTHDERINST
ifneq ($(strip $(DFTHDER)),)
ifneq ($(strip $(DFTHDERINST)),)
	@if [ ! -d "$(DFTHDERINST)" ] ; then \
		echo $(MKDIR) $(DFTHDERINST) ; \
		$(MKDIR) $(DFTHDERINST) ; \
	fi ; \
	for FILE in `echo $(DFTHDER)` ; do \
		echo $(CP) $$FILE $(DFTHDERINST)/ ; \
		$(RM) $(DFTHDERINST)/$$FILE ; \
		$(CP) $$FILE $(DFTHDERINST)/ ; \
	done
endif
endif
#- make_install_DFTHDERINST
#+ make_install_OBJINST
ifneq ($(strip $(OBJ)),)
ifneq ($(strip $(OBJINST)),)
	@if [ ! -d "$(OBJINST)" ] ; then \
		echo $(MKDIR) $(OBJINST) ; \
		$(MKDIR) $(OBJINST) ; \
	fi ; \
	for FILE in `echo $(OBJ)` ; do \
		echo $(CP) $$FILE $(OBJINST)/ ; \
		$(RM) $(OBJINST)/$$FILE ; \
		$(CP) $$FILE $(OBJINST)/ ; \
	done
endif
endif
#- make_install_OBJINST
#+ make_install_OBJINST2
ifneq ($(strip $(OBJ2)),)
ifneq ($(strip $(OBJINST2)),)
	@if [ ! -d "$(OBJINST2)" ] ; then \
		echo $(MKDIR) $(OBJINST2) ; \
		$(MKDIR) $(OBJINST2) ; \
	fi ; \
	for FILE in `echo $(OBJ2)` ; do \
		echo $(CP) $$FILE $(OBJINST2)/ ; \
		$(RM) $(OBJINST2)/$$FILE ; \
		$(CP) $$FILE $(OBJINST2)/ ; \
	done
endif
endif
#- make_install_OBJINST2
#+ make_install_NOCLEAN_OBJINST
ifneq ($(strip $(NOCLEAN_OBJ)),)
ifneq ($(strip $(NOCLEAN_OBJINST)),)
	@if [ ! -d "$(NOCLEAN_OBJINST)" ] ; then \
		echo $(MKDIR) $(NOCLEAN_OBJINST) ; \
		$(MKDIR) $(NOCLEAN_OBJINST) ; \
	fi ; \
	for FILE in `echo $(NOCLEAN_OBJ)` ; do \
		echo $(CP) $$FILE $(NOCLEAN_OBJINST)/ ; \
		$(RM) $(NOCLEAN_OBJINST)/$$FILE ; \
		$(CP) $$FILE $(NOCLEAN_OBJINST)/ ; \
	done
endif
endif
#- make_install_NOCLEAN_OBJINST
#+ make_install_SQLINST
ifneq ($(strip $(SQL)),)
ifneq ($(strip $(SQLINST)),)
	@if [ ! -d "$(SQLINST)" ] ; then \
		echo $(MKDIR) $(SQLINST) ; \
		$(MKDIR) $(SQLINST) ; \
	fi ; \
	for FILE in `echo $(SQL)` ; do \
		echo $(CP) $$FILE $(SQLINST)/ ; \
		$(RM) $(SQLINST)/$$FILE ; \
		$(CP) $$FILE $(SQLINST)/ ; \
	done
endif
endif
#- make_install_SQLINST
