
RM ?= rm -f

CXX = clang++

SRC = AGraphical.cpp AModule.cpp ClockModule.cpp CpuModule.cpp DataStruct.cpp NCURSESGraphical.cpp NetworkModule.cpp OsModule.cpp ProgramGlsl.cpp RamModule.cpp Renderer.cpp Shader.cpp TextRenderer.cpp Texture.cpp UserModule.cpp Window.cpp fontBmp.cpp get_config.cpp main.cpp
# SRC = main.cpp Window.cpp Shader.cpp ProgramGlsl.cpp \
	TextRenderer.cpp Texture.cpp Renderer.cpp
SRCS = $(addprefix src/, $(SRC))

OBJS = $(addprefix obj/, $(SRC:.cpp=.o))
DEPS = $(addprefix dep/, $(SRC:.cpp=.d))

CPPFLAGS = -Wall -Wextra -Werror -I include \
	`pkg-config --cflags glfw3` \
	`pkg-config --cflags glew` \
	-std=c++98

LDFLAGS= `pkg-config --static --libs glfw3` \
	`pkg-config --static --libs glew` \
	-framework OPENGL -lncurses
LDLIBS=


NAME = ft_gkrellm
.PHONY: all clean fclean run debug re run


default:all


all: $(NAME)

$(NAME): $(DEPS) $(OBJS)
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

obj/%.o: src/%.cpp
	$(CXX) -o $@ -c $< $(CPPFLAGS)
dep/%.d: src/%.cpp
	@echo "generate $@"
	@set -e; $(RM) $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,obj/\1.o $@ : ,g' < $@.$$$$ >> $@; \
		$(RM) $@.$$$$

depend: $(DEPS)

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
fclean:clean
	$(RM) $(NAME)
	$(RM) .depend
re:fclean all
run:
	./$(NAME) $(ARGS)
debug:all run

-include $(DEPS)
