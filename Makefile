# CC -- the c compiler to use
# CXX -- the c++ compiler to use
# LD -- the linker to use
# CFLAGS -- compilation flag for c source files
# CXXFLAGS -- compilation flags for c++ source files
# CPPFLAGS -- flags for the c-preprocessor (typically include file paths and symbols defined on the command line), used by c and c++
# LDFLAGS -- linker flags
# LDLIBS -- libraries to link

LDFLAGS = -std=c++0x -pthread
CXXFLAGS = -std=c++11
CXX = g++

src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

all:latecall

latecall: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

-include $(dep) #include all dependency files in makefile

%.d:src/%.cpp
	@$(CPP) $(CPPFLAGS) $< -MM -MT $(@:.d:.o) >$@#preprocessor will generate a makefile rule

.PHONY: clean
clean:
	rm -f $(obj) latecall

.PHONY: cleandep
cleandep:
	rm -f $(dep)

.PHONY: install
install: latecall
	mkdir -p /usr/local/share/lc
	cp $< /usr/local/bin/latecall
	cp data/latecall.ini /usr/local/etc/latecall.ini
	cp data/def_prelc.sh /usr/local/share/lc/def_prelc.sh
	cp data/def_lc.sh /usr/local/share/lc/def_lc.sh
	cp data/sendMail2.py /usr/local/share/lc/sendMail2.py
	cp data/latecall.service /etc/systemd/system/latecall.service
	chmod 777 /usr/local/bin/latecall
	chmod 777 /usr/local/share/lc/def_prelc.sh
	chmod 777 /usr/local/share/lc/def_lc.sh
	chmod 777 /usr/local/share/lc/sendMail2.py
	chmod 444 /usr/local/etc/latecall.ini
	chmod 444 /etc/systemd/system/latecall.service
	systemctl enable latecall

.PHONY:uninstall
uninstall:
	rm -f /usr/local/bin/latecall
	rm -f /usr/local/etc/latecall.ini
	rm -rf /usr/local/share/lc
	systemctl stop latecall
	systemctl disable latecall
	rm -f /etc/systemd/system/latecall.service

#Reserves...
# %.o: %.cpp
#     $(CXX) $(CXXFLAGS) -o $@ -c $<