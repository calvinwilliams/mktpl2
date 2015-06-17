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

#+ dir_make
# make规则
.PHONY:make
make	:
	@for %%i in ($(DIROBJS)) do ( \
		if exist %%i \
		( \
			if exist "%%i/makefile$(MAKEFILE_POSTFIX)" \
			( \
				$(CD) %%i && \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) && \
				$(CD) .. \
			) \
		) && \
		if not errorlevel 0 \
		( \
			exit \
		) \
	)
#- dir_make

#+ dir_clean
# clean规则
.PHONY:clean
clean	:
	@for %%i in ($(DIROBJS)) do ( \
		if exist %%i \
		( \
			if exist "%%i/makefile$(MAKEFILE_POSTFIX)" \
			( \
				$(CD) %%i && \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) clean && \
				$(CD) .. \
			) \
		) && \
		if not errorlevel 0 \
		( \
			exit \
		) \
	)
#- dir_clean

#+ dir_install
# install规则
.PHONY:install
install	:
	@for %%i in ($(DIROBJS)) do ( \
		if exist %%i \
		( \
			if exist "%%i/makefile$(MAKEFILE_POSTFIX)" \
			( \
				$(CD) %%i && \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) install && \
				$(CD) .. \
			) \
		) && \
		if not errorlevel 0 \
		( \
			exit \
		) \
	)
#- dir_install

#+ dir_uninstall
# uninstall规则
.PHONY:uninstall
uninstall	:
	@for %%i in ($(DIROBJS)) do ( \
		if exist %%i \
		( \
			if exist "%%i/makefile$(MAKEFILE_POSTFIX)" \
			( \
				$(CD) %%i && \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) uninstall && \
				$(CD) .. \
			) \
		) && \
		if not errorlevel 0 \
		( \
			exit \
		) \
	)
#- dir_uninstall

