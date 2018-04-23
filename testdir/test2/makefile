# 此文件由makeobj.sh自动生成
############################################################
# 项目名 : 
# 模块名 : 
# 备  注 : 
############################################################

###### 源文件配置区
#@ SQC_FILE
SQC_FILE	=	\
			test2.SQC \

###### 目标文件、安装目录配置区
BIN		=	test2
BININST		=	$(HOME)/bin

###### 编译选项
CFLAGS		=	-I. \

###### 链接选项
LFLAGS		=	-L. \
			-L$(ORACLE_HOME)/lib \
			-lorasdk \

###### 额外宏定义区
CLEAN_ADDITION	=

###### 加载mktpl模板库
#@ make_all
#@ make_clean
#@ make_install
#@ make_install_BININST
#@ make_install_DFTHDERINST

include $(MKTPL2_HOME)/makeobj_$(MKTPL2_OS).inc

###### 目标文件依赖关系
test2		:	$(SQC_FILE_o)
	$(CC) -o $@ $(SQC_FILE_o) $(LFLAGS)

