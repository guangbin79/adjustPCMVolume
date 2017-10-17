```shell
gcc adjustPCMVolume.c -o volume 
./volume pcm.raw 1.8
```
```shell
ffplay -f s16le -ar 44100 -ac 2 adjusted_pcm.raw
```
