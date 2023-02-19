#
# Created by XMAKE Version 5.2.0 on Thu Jan 25 13:08:21 2001
#
# The following options were used: -O -R -X 
#
# The following is the hierarchy of the design 'ev03.xnf'
#
# ev03.xnf
#     fdr.xnf
#         fd.xnf
#     fdr.xnf
#     fdr.xnf
# 
DEFAULT_TARGET ev03.xff

ev03.bit : ev03.lca 
	makebits ev03.lca

ev03.lca : ev03.map 
	map2lca -P 3020PC68-70 ev03.map ev03.lca
	apr -W ev03.lca ev03.lca

ev03.map : ev03.xtf 
	xnfmap -P 3020PC68-70 ev03.xtf ev03.map

ev03.xtf : ev03.xff 
	xnfprep ev03.xff ev03.xtf parttype=3020PC68-70

ev03.xff : fd.xnf fdr.xnf ev03.xnf 
	xnfmerge -P 3020PC68-70 ev03.xnf ev03.xff

