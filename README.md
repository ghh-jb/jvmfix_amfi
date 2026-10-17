# jvmfix_amfi
Library that should be preloaded (via DYLD_INSERT_LIBRARIES) to java for it to work with amfi_get_out_of_my_way=1. Use for example with shell's conf.

# Problem
https://github.com/corretto/corretto-11/issues/385

I really wanted to play minecraft with friends but because I was planning to use vPhone as research machine I disabled AMFI and ran into this issue.

# Build
1. Install theos and Xcode
2. Point macosx SDK from Xcode dir to theos sdks
3. Run make package install from project directory. (dont forget to change root password to successfully login into root at install)
4. Profit?

# Usage
The library will be installed to /opt/homebrew/lib/jvmfix_noamfi.dylib
In your shell's conf file (bashrc/zshrc or fish.conf) specify ```export DYLD_INSERT_LIBRARIES="/opt/homebrew/lib/jvmfix_noamfi.dylib"``` to load it into every process started from that shell.

# How?
Pretty easy, it just sets SIGBUS handler where it fixes JIT memory protection. When java binary (or anything else) exits with sigbut it intercepts it and the binery cntinues execution.

Thanks to @khanduytran0 for the fix.

# License
MIT. See the ```LICENSE``` file.