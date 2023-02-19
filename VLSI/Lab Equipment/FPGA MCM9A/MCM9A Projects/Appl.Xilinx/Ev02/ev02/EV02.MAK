#
# Created by XMAKE Version 5.2.0 on Tue Jan 23 17:24:00 2001
#
# The following options were used: -O -R -X 
#
# The following is the hierarchy of the design 'ev02.xnf'
#
# ev02.xnf
#     fdc.xnf
#     x74_162.xnf
#         ftrsle.xnf
#             m2_1.xnf
#             fdre.xnf
#                 fd.xnf
#         ftrsle.xnf
#         ftrsle.xnf
#         ftrsle.xnf
#     x74_162.xnf
#     x74_162.xnf
#     x74_162.xnf
#     x74_162.xnf
#     x74_162.xnf
#     fdc.xnf
#     m4_1e.xnf
#         m2_1.xnf
#         m2_1.xnf
#         m2_1e.xnf
#     x74_162.xnf
#     x74_162.xnf
#     m4_1e.xnf
#     m4_1e.xnf
#     d2_4e.xnf
#     m4_1e.xnf
# 
DEFAULT_TARGET ev02.xff

ev02.bit : ev02.lca 
	makebits ev02.lca

ev02.lca : ev02.cst ev02.map 
	ppr ev02.map parttype=3020APC68-7
	xdelay -D -W ev02.lca

ev02.map : ev02.xtf 
	xnfmap -P 3020APC68-7 ev02.xtf ev02.map

ev02.xtf : ev02.xff 
	xnfprep ev02.xff ev02.xtf parttype=3020APC68-7

ev02.xff : d2_4e.xnf m2_1e.xnf m4_1e.xnf fd.xnf fdre.xnf m2_1.xnf ftrsle.xnf \
x74_162.xnf fdc.xnf ev02.xnf 
	xnfmerge -P 3020APC68-7 ev02.xnf ev02.xff

