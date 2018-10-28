

RM := rm -fr

TARGETS := src/transcode src/info src 

.PHONY: all $(TARGETS)
all: MAKEFLAGS = all
all: $(TARGETS)

.PHONY: clean $(TARGETS)
clean: MAKEFLAGS = clean
clean: $(TARGETS)






$(TARGETS):
	$(MAKE) -C $@ $(MAKEFLAGS)
	

	
