STM32的flash共512KB

| 扇区编号 | 起始地址    | 大小   | 描述                         |
| -------- | ----------- | ------ | ---------------------------- |
| Sector 0 | 0x0800_0000 | 16 KB  | 小扇区，常用于 Boot 启动代码 |
| Sector 1 | 0x0800_4000 | 16 KB  |                              |
| Sector 2 | 0x0800_8000 | 16 KB  |                              |
| Sector 3 | 0x0800_C000 | 16 KB  |                              |
| Sector 4 | 0x0801_0000 | 64 KB  | 可用于参数存储、升级数据等   |
| Sector 5 | 0x0802_0000 | 128 KB | 主程序区（App）              |
| Sector 6 | 0x0804_0000 | 128 KB |                              |
| Sector 7 | 0x0806_0000 | 128 KB |                              |

需要分配flahs的内容有：

1. bootloader   扇区0、扇区1   <32kb
2. app1              扇区5                <128kb
3. app2              扇区6                <128kb
4. configure      扇区7                <128kb
5. device info   扇区2、扇区3   <32kb