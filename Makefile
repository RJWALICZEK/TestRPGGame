# Kompilator i flagi
CXX = clang++ 
CXXFLAGS = -g -Wall -Werror -std=c++17

# Znajdujemy pliki źródłowe .cpp i nagłówkowe .h,
# ignorując katalog .ccls-cache
SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.cpp' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

# Domyślna reguła: kompiluj wszystkie źródła i nagłówki do main
main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

# Debug build bez hardeningu i z zerową optymalizacją
main-debug: $(SRCS) $(HEADERS)
	NIX_HARDENING_ENABLE= $(CXX) $(CXXFLAGS) -O0 $(SRCS) -o $@

# Czyszczenie plików tymczasowych i plików wynikowych
clean:
	rm -f main main-debug *.o
	rm -rf .ccls-cache
