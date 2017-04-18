## C 文件编译过程

hello.c

```c
#include <stdio.h>

int main(){
	printf("hello, world\n");
}
```

编译过程：
<pre><code class="language-C"> <i>hello.c</i>
	|
	|
	v
<b>预处理器(cpp)</b>
	|
	|
	v
 <i>hello.i</i>
	|
	|
	v
 <b>编译器(ccl)</b>
	|
	|
	v
 <i>hello.s</i>
	|
	|
	v
 <b>汇编器(as)</b>
	|
	|
	v
 <i>hello.o</i>
	|
	|
	v
 <b>链接器(ld)</b>
	|
	| <i>printf.o</i>
	v
 <i>hello.out</i>
</code></pre>

- 预处理器： 仅处理预编译指令
- 编译阶段： 将 c 代码编译为汇编语言
- 汇编阶段： 将汇编语言翻译成二进制文件
- 链接阶段： 将需要链接的目标文件加载到内存
