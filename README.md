# Decrypt-Souyinke
A decrypt tool for files encrypt by com.soyinke.mdzz.android.util

souyinke是一个古老的有声小说APP

它提供了很多独家的有声小说，并可以离线下载

但是它的离线下载版本是经过加密的

加密方式超级简单，字母表移位加密

这个工具能够把加密文件还原回去

conv.c是还原工具，dec.c是分析文件差异使用，rename.sh是用于恢复文件名

用法：./conv 输入文件夹 输出文件夹

仅供学习交流，请不要用于其他用途
