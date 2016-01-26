Cs Great Mistake
================

The C programming language is probably the single most important language in the history of computing thus far. Most code in production anywhere is running on a platform which was implemented in the language. Many of the computing systems we rely upon daily are written in it. And most higher level languages are implemented in it or it&#39;s offspring. <br><br>C is not a perfect language, or even a terribly compelling language.  It is, however, a spartan language closely matching the abstract virtual machine implemented in most popular processors.   When you think of Intel x86, you probably don&#39;t think of it as a Pascal machine (but it was at one time) but in terms of a C machine.  You probably don&#39;t think of Sparc in terms of Java, but in how it maps to C.   In fact, many of the the instructions which made Pascal and Basic fast on x86 in yesteryear, have been largely abandoned in favor of making the instructions which are C friendly faster.   When was the last time you wrote a program with hardware accelerated binary encoded decimal addition?  Unless you whipped out you asm() macro, your compiler probably doesn&#39;t even expose those instructions. <br><br>Most of what defines a fast processor today is how well does it run C code. Make no mistake, hardware manufacturers play favorites, and to constantly improve their benchmarks design chips which try to do better than the compiler. Often simplistic unoptimized algorithm performs better in practice, than well design algorithms, because the hardware engineers optimized for simplistic code generators. If adding some circuitry to speed up some poorly written but important benchmark or application makes for significant sales, those circuits will be added. <br><br>That being said, the C virtual machine model has some design trade offs that implicitly restrict what most programmers view as possible. Probably the most important of these is the way in which function calls are implemented.   C language does not allow for returning anything more complex than a single value which must fit within a register.   This means that if multiple values are returned from a function, they must be returned by reference.<br><br>  This limitation is a side effect of a decision regarding the usage of the stack as both a means to transfer data and flow control between functions as a form of modularization.  Since C allowed the caller to pass a variable number of arguments on the stack to a function defined in a separate compilation module, it required the caller and not the callee to clean up the stack.  The callee has no metadata describing the structure of the stack, it may or may not create its own stack frame (preserving the value of the old frame pointer) but C does not guarantee this to be the case.  Most processors also push the next  instruction pointer address after the call instruction onto the stack.  This allows the callee to return control to the caller.  Between the stack frame pointer and the return address, and any local data on the stack, a callee must reset the stack to the state it was prior to its execution, usually bcore storing the old frame pointer and allowing the return instruction to consume the continuation address.<br><br> As such,  the C calling convention avoids returning a value on the stack. Instead most ABIs dedicate a register to hold the return value. Since functions are typically compiled as reusable units, each function uses the same register for its return value.  Since these two design objectives mean that all C programs are limited in how they structure argument passing.  Typically, a caller will not only adjust the stack pointer to consume the parameters upon return, but also juggle the return results into a local stack slot so as not to loose the result when a second function is called.  Even with single static assignment and register coloring, modern compilers can not work around these aliasing issues that arise from the modularity objective. <br><br>Most modern C ABIs avoid explicit stack usage for parameter passing. Sparc, ARM, and x86_64 all define register based ABIs for their platforms. In these schemes a set of registers are dedicated to specific parameters, and are consumed in order.  This allows the hardware to internally alias registers while exposing only a small fraction of the hardware register file to the programmer. In the case of x86_64, 8 general purpose registers and 8 floating point registers are dedicated to the ABI, one additional register is deemed reserved as well as it is not guaranteed to be preserved on system calls, but 7 general purpose registers remain available for local storage.  This allocation strategy allows most small functions to entirely avoid touching the heap or stack, but ensure that anything other than a simple scalar value will be returned via heap reference in register rax. <br><br>While this change in convention dramatically reduces the number of L1 memory fetches, it also preserves a strange fact about the C programming language: it struggles with destructuring and composition.  Take for example the concept:<br><br>F(x,y) -> (x&#39;,y&#39;,z)<br>G(x,y,z) -> (x&#39;,y&#39;,z&#39;)<br>H(x,y,z) -> ()<br><br>H(G(F(1,2),3)) -> ()<br><br>Now in a language like Perl, or Ruby, or any language in the ML family with partial application, you can efficiently write this sort of composition, as the languages support destructuring.  There is no need for intermediate values, and explicit destructuring. In C, although you can pass all three values in registers, you can not return all 3 unless the resulting structure can be fit within a single register. In effect you are forced to juggle these values by hand with temporary registers:<br><br>a = F(1,2)<br>b = G(a->x, a->y, 3)<br>H(b->x, b->y, b->z)<br><br>What is interesting here is you can think of the value passed to a C function as a structure on the stack:<br><br>  (int a,int b,int c) == { int a, b, c };<br><br>But the C language is incapable of making this jump because all functions from the callee&#39;s view are arbitrary structures of potentially infinite length.   In other words, they all appear to be (...) where ... can be anything.  But this function must map those arbitrary parameters to a single simple scalar so that the continuation can be called efficiently. That is to say the current continuation of each C function is explicitly:<br><br>void  cc( register a);<br><br>Which is rather odd when you consider that you can generally pass any function an arbitrary numbers of arguments. But since the continuation invocation is rolled into the explicit return statement which takes either 0 or 1 argument, it is impossible to call a continuation with more than one argument.   <br><br>This is not to say the language could not be extended to do so, but that would require either the caller to expect arguments in the registers of the ABI or would require a more drastic change, the separation of flow control stack from the data stack.   If the callee can accept an arbitrary number of arguments and can return an arbitrary number of arguments, both the callee and caller need a way to specify both how many values were pushed on the stack and how many we&#39;re returned. If the data stack were explicitly furnished with return values, the caller would only need to compare the difference between the current stack pointer and its value just prior to the call. This would let the caller squirrel away the return values and also clean up after itself.   The values returned could be destructured, rearranged, or passed immediately to the next function.  Languages like Forth and some Perl make active use of this calling pattern.  The added flexibility allows for code that avoids boxing and unboxing values.<br><br>The main limitation in this scheme from the point of view of most modern ABIs is that they allocate registers instead of stack values. As such, they have no explicit argument count on functions with less than 9 arguments (18 in te case of mixed integer and floating arguments).  This means many programs never clean up a stack as they never touch it in practice.  To implement this scheme one would need to dedicate another register or two to keep the count of the number of arguments passed in each register file. <br><br>This would have two major effects:  you wouldn&#39;t be guessing ever as to how many arguments were passed and you could use the same mechanism to safely return multiple values. In fact any structure of 64bytes or less could be passed in integer registers alone. <br><br>This oddity of the C language has produced more overly clever work arounds. In most environments, the return value is only used to indicate error status, with all actual return values passed by reference by mutating pointers passed to the function. If you look at a function like fstat, you&#39;ll see code like:<br><br>  if(error = fstat(fd,&stat_st)) {<br>      // handle error here<br>  }<br><br>The actual return value of fstat is a structure of data passed in by reference. Since fstat can not return a structure, it returns an error code, which is also set in a global errno, which our code effectively doubles.  Or take mmap which makes a return value do double duty, being either an error code or a pointer to a region of memory:<br><br>  if(MAP_FAILED == (ptr = mmap(NULL,4096,PROT_READ,MAP_SHARED|MAP_FILE,fd,0))) {<br>  // do error handling here<br>  }<br><br>We also have a subtle error in the above code, in that ptr could also be NULL, which would also be an error, but we can not reliably test, as some optimizers will commute an || operator.  As such we must move our assignment outside of the test to ensure order of operation does not matter. <br><br>Now this may all seem like quibbling over a minor detail, but it is fundamental to how all software in the real world works. Because of these two design trade offs, most core system modules are designed to share memory. Since you cannot return structures in C, your application and system code must share memory access to communicate.  Likewise, use of a third party library requires you share memory to perform most complex operations. All of this sharing increases the complexity of garbage collection, and ensures the production of more garbage. Additionally, since some shared regions are static, where others are not, it provides ample opportunity for mistaken free calls, producing opportunities security bugs. <br><br>Since the memory is shared, threading on multiple CPUs often results in lock contention, and a greater deal of mutexs and other semaphores are needed to coordinate across processor boundaries.  This makes C a difficult language to parallelize, and an even more difficult language to debug.  If one looks at debugging on C, one must invoke a debugger which forces the CPU into a special mode. The IRQ that traps each instruction step, triggers the debugger to resume operation on each step. But since the values passed are in registers, with some values shadowed on the stack, and others stored on the heap, knowing which value is significant depends on the aliasing at that point in time. If one omits stack frames, the debugger can not compensate. In many cases the actual value you are looking for from the source will have been "optimized away", but if that very optimization is the source of the bug, you&#39;re S.O.L. <br><br>The C language calling convention and various ABIs are a product of a feedback loop. Early CPU designers added support for popular programming languages of the day. Intel x86 has a RETN instruction which makes the Pascal calling convention where the callee cleans up the stack trivial for example.  The C calling convention doesn&#39;t benefit from the RETN instruction, and few code generators will produce a RETN in any output.  In fact, many of these non-C instruction are largely unused in modern software. What has been introduced to benefit C, however, is position relative addressing for all operations. This allows the CPU&#39;s instruction pointer to float around in absolute addressing terms, but always maintain its data section at a fixed relative offset to the instruction.  The net effect being that C&#39;s position independent code generation becomes vastly more efficient than before through hardware support. This change was necessary to support security models for C code, where libraries are linked at random addresses to prevent overflow bugs from calling specific code which provided a privilege escalation. <br><br>Position independent code, in the C sense, is not terribly useful to programming languages in general. Most OO languages use a base object pointer and address relative to it, and not a fixed address in a static allocation.  PIC code also reduces the cost of the C trampolines which allow for symbolic linking. Since C&#39;s other great mistake, a singular flat namespace for each process governed by simple string lookups, relies upon a runtime dispatch table for external references in linked libraries, C usually requires 2 or more memory accesses to fix a function call address.  In cases where hot patching is necessary, such as on Windows, each jump location is also prefixed with a large no-op so that the function can be patched with a jump to a patch table.  These sorts of indirections are necessary to support basic module loading, though no unloading scheme exists. This means that modification of running code is a one way street. You can add libraries at run time, but the C call dispatch mechanisms are designed for simple call redirection, and not runtime modification and hot deployment. <br><br>In practice, the C calling conventions not only limit what is possible, but make substantial improvement to the engineering state of the art difficult to obtain.  C&#39;s legacy not only shapes how systems are designed, but also frame the discussion in the first place.  Many features of more modern languages like destructuring, pattern matching, dynamic dispatch, hot code loading and unloading, runtime editing and resumption, intercall optimizations, and partial functions have all remained the domain of very high level languages emulated in C.  Many of these features have made their way into languages like C++ and Objective-C through the addition of a run time library, but the essentials of most systems have remained unaffected by these advances. C&#39;s legacy is its burden, and the great mistakes of the past will carry along with us long into the future. 