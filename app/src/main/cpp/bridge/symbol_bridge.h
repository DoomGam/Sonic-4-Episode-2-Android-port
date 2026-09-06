#ifndef SYMBOL_BRIDGE_H
#define SYMBOL_BRIDGE_H

extern "C" {
    void* resolve_ios_symbol(const char* name);
}

#endif // SYMBOL_BRIDGE_H
