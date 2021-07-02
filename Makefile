SERVER	= server
CLIENT	= client

CC		= gcc
RM		= rm -rf
# ERFLG	= -fsanitize=address
 CFLAGS	= -Wall -Wextra -Werror -g $(ERFLG)

LIBFT	= -L ./libft -lft
HEDER	= *.h

# SRC	:= $(wildcard *.c)
SRC		:= utils_minitalk.c
S_SRC	=	$(SRC) server.c
C_SRC	=	$(SRC) client.c

OBJDIR	= .obj
S_OBJ	= $(S_SRC:%.c=$(OBJDIR)/%.o)
C_OBJ	= $(C_SRC:%.c=$(OBJDIR)/%.o)

DEPDIR	= .dep
DEPFILES = $(S_SRC:%.c=$(DEPDIR)/%.d) $(C_SRC:%.c=$(DEPDIR)/%.d)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d


all: $(SERVER) $(CLIENT)

$(SERVER): $(S_OBJ) $(HEDER)
	@echo "$(CLRCY)Подключение$(CLRPR)$(LIBFT)$(CLRRS)"
	@$(CC) $(CFLAGS) $(LIBFT) $(S_OBJ) -o $@
	@echo "$(CLRCY)Создан$(CLREL)$@$(CLRRS)"

$(CLIENT): $(C_OBJ) $(HEDER)
	@echo "$(CLRCY)Подключение$(CLRPR)$(LIBFT)$(CLRRS)"
	@$(CC) $(CFLAGS) $(LIBFT) $(C_OBJ) -o $@
	@echo "$(CLRCY)Создан$(CLREL)$@$(CLRRS)"
	
$(OBJDIR)/%.o: %.c | $(OBJDIR) $(DEPDIR)
	@$(MAKE) -C ./libft
	@echo "$(CLRCY)Создан$(CLRGR)$@$(CLRRS)"
	@$(CC) -c $(CFLAGS) $(DEPFLAGS) -o $@ $<

$(OBJDIR) $(DEPDIR):
	@mkdir -p $@

$(DEPFILES):
include $(wildcard $(DEPFILES))

re:
	@$(MAKE) fclean
	@$(MAKE) all

clean:
	@$(MAKE) clean -C ./libft
	@$(RM) $(OBJDIR) $(DEPDIR)
	@echo "$(CLRCY)Очистка$(CLRRE)$(OBJDIR)$(DEPDIR)$(CLRRS)"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(SERVER) $(CLIENT)
	@echo "$(CLRCY)Удаление$(CLRRE)$(SERVER) $(CLIENT)$(CLRRS)"

gitpush: fclean
	git status
	git add *.c *.h Makefile libft/
	git commit -m "New edition"
	git push

.PHONY: all clean fclean re

#-c говорит не запускать линкер, потому что нет main
#-g порождает отладочную информацию в родном формате операционной системы
#включает использование дополнительной отладочной информации, 
#которую может использовать только GDB; 
#эта дополнительная отладочная информация делает работу отладки в GDB лучше, но может, 
#вероятно испортить работу других отладчиков, или помешать им прочитать программу.

CLRRS = \033[0m #сброс цвета
BOLDf = \033[1m #жирный шрифт
UNDRL = \033[4m #подчеркивание
FONGR = \033[47m #серый цвет фона
CLRGR = \033[37m #серый цвет шрифта
FONCY = \033[46m #цвет морской волны фона		
CLRCY = \033[36m #цвет морской волны шрифта
FONPR = \033[45m #фиолетовый цвет фона
CLRPR = \033[35m #фиолетовый цвет шрифта
FONBL = \033[44m #синий цвет фона
CLRBL = \033[34m #синий цвет шрифта
FONEL = \033[43m #желтый цвет фона
CLREL = \033[33m #желтый цвет шрифта
FONGR = \033[42m #зелёный цвет фона
CLRGR = \033[32m #зелёный цвет шрифта
FONRE = \033[41m #красный цвет фона
CLRRE = \033[31m #красный цвет шрифта
FONBC = \033[40m #чёрный цвет фона
CLRBC = \033[30m #чёрный цвет шрифта
#COLOR+FON = \033[6;35m - можно совмещать \033[6 - цвет шрифта ;35m - цвет фона