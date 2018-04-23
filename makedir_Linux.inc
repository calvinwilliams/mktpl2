######################################################################
# mktpl v2.0.0 - makefile模板库
# copyright by calvin 2013
# calvinwilliams.c@gmail.com
#
# 使用工具makeobj.sh、makedir.sh自动生成或编写最小化makefile
# ，装载公共规则库实现makefile
# 或 然后用工具makelocal.sh本地化展开生成独立使用makefile
######################################################################

#################### 目录递归推导规则 ####################

#+ FILESYSTEM
# 文件系统宏
CD		=	cd
RM		=	rm -f
CP		=	cp -f
MV		=	mv -f
MKDIR		=	mkdir -p
#- FILESYSTEM

#+ dir_all
# 最终目标列表
all		:	make
#- dir_all

#+ dir_prepro_all
# make规则
.PHONY:prepro_all
prepro_all	:
	@for i in $(DIROBJS) ; do \
		if [ -d "$$i" ] ; then \
			if [ -f "$$i/makefile$(MAKEFILE_POSTFIX)" ] ; then \
				$(CD) $$i ; \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) prepro_all ; \
				if [ $$? -ne 0 ] ; then \
					exit 1 ; \
				fi ; \
				$(CD) .. ; \
			fi ; \
		fi ; \
	done
#- dir_prepro_all

#+ dir_make
# make规则
.PHONY:make
make	:
	@for i in $(DIROBJS) ; do \
		if [ -d "$$i" ] ; then \
			if [ -f "$$i/makefile$(MAKEFILE_POSTFIX)" ] ; then \
				$(CD) $$i ; \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) ; \
				if [ $$? -ne 0 ] ; then \
					exit 1 ; \
				fi ; \
				$(CD) .. ; \
			fi ; \
		fi ; \
	done
#- dir_make

#+ dir_clean
# clean规则
.PHONY:clean
clean	:
	@for i in $(DIROBJS) ; do \
		if [ -d "$$i" ] ; then \
			if [ -f "$$i/makefile$(MAKEFILE_POSTFIX)" ] ; then \
				$(CD) $$i ; \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) clean ; \
				if [ $$? -ne 0 ] ; then \
					exit 1 ; \
				fi ; \
				$(CD) .. ; \
			fi ; \
		fi ; \
	done
#- dir_clean

#+ dir_install
# install规则
.PHONY:install
install	:
	@for i in $(DIROBJS) ; do \
		if [ -d "$$i" ] ; then \
			if [ -f "$$i/makefile$(MAKEFILE_POSTFIX)" ] ; then \
				$(CD) $$i ; \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) install ; \
				if [ $$? -ne 0 ] ; then \
					exit 1 ; \
				fi ; \
				$(CD) .. ; \
			fi ; \
		fi ; \
	done
#- dir_install

#+ dir_uninstall
# uninstall规则
.PHONY:uninstall
uninstall	:
	@for i in $(DIROBJS) ; do \
		if [ -d "$$i" ] ; then \
			if [ -f "$$i/makefile$(MAKEFILE_POSTFIX)" ] ; then \
				$(CD) $$i ; \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) uninstall ; \
				if [ $$? -ne 0 ] ; then \
					exit 1 ; \
				fi ; \
				$(CD) .. ; \
			fi ; \
		fi ; \
	done
#- dir_uninstall

