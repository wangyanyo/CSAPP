写一个动态内存分配器，一个版本一个版本的迭代更新。
1. 隐式空闲链表 + 立即合并 + 无垃圾回收
2. 边界优化隐式空闲链表 + 立即合并 + 无垃圾回收
3. 显式空闲链表 + 立即合并 + 无垃圾回收
4. 简单分离空闲链表 + 立即合并 + 无垃圾回收
5. 分离适配空闲链表 + 立即合并 + 无垃圾回收
6. 伙伴系统 + 立即合并 + 无垃圾回收
7. 分离适配空闲链表 + 延迟合并 + 无垃圾回收
7. 分离适配空闲链表 + 延迟合并 + 垃圾回收

我希望每写完一个版本，都去搜索一下官方是怎么写的，然后做出对应修改，并且想办法评估内存利用率和运行效率。