double len=159; 
static double ref_profile[][4]={ 
0.00000000, 0.00000000, 0.00000000, 0.00000000, 
0.00021035, 0.00841412, 0.00000000, 0.00000000, 
0.00084141, 0.01682823, 0.00000000, 0.00000000, 
0.00189318, 0.02524235, 0.00000000, 0.00000000, 
0.00336565, 0.03365647, 0.00000000, 0.00000000, 
0.00525882, 0.04207058, 0.00000000, 0.00000000, 
0.00757270, 0.05048470, 0.00000000, 0.00000000, 
0.01030729, 0.05889881, 0.00000000, 0.00000000, 
0.01346259, 0.06731293, 0.00000000, 0.00000000, 
0.01703859, 0.07572705, 0.00000000, 0.00000000, 
0.02103529, 0.08414116, 0.00000000, 0.00000000, 
0.02545270, 0.09255528, 0.00000000, 0.00000000, 
0.03029082, 0.10096940, 0.00000000, 0.00000000, 
0.03554964, 0.10938351, 0.00000000, 0.00000000, 
0.04122917, 0.11779763, 0.00000000, 0.00000000, 
0.04732940, 0.12621174, 0.00000000, 0.00000000, 
0.05385034, 0.13462586, 0.00000000, 0.00000000, 
0.06079199, 0.14303998, 0.00000000, 0.00000000, 
0.06815434, 0.15145409, 0.00000000, 0.00000000, 
0.07593740, 0.15986821, 0.00000000, 0.00000000, 
0.08414116, 0.16828233, 0.00000000, 0.00000000, 
0.09276563, 0.17669644, 0.00000000, 0.00000000, 
0.10181081, 0.18511056, 0.00000000, 0.00000000, 
0.11127669, 0.19352468, 0.00000000, 0.00000000, 
0.12116328, 0.20193879, 0.00000000, 0.00000000, 
0.13147057, 0.21035291, 0.00000000, 0.00000000, 
0.14219857, 0.21876702, 0.00000000, 0.00000000, 
0.15334727, 0.22718114, 0.00000000, 0.00000000, 
0.16491668, 0.23559526, 0.00000000, 0.00000000, 
0.17690680, 0.24400937, 0.00000000, 0.00000000, 
0.18931762, 0.25242349, 0.00000000, 0.00000000, 
0.20214914, 0.26083761, 0.00000000, 0.00000000, 
0.21533407, 0.26252043, 0.00000000, 0.00000000, 
0.22824973, 0.25410631, 0.00000000, 0.00000000, 
0.24074470, 0.24569220, 0.00000000, 0.00000000, 
0.25281895, 0.23727808, 0.00000000, 0.00000000, 
0.26447250, 0.22886396, 0.00000000, 0.00000000, 
0.27570535, 0.22044985, 0.00000000, 0.00000000, 
0.28651749, 0.21203573, 0.00000000, 0.00000000, 
0.29690892, 0.20362162, 0.00000000, 0.00000000, 
0.30687965, 0.19520750, 0.00000000, 0.00000000, 
0.31642967, 0.18679338, 0.00000000, 0.00000000, 
0.32555899, 0.17837927, 0.00000000, 0.00000000, 
0.33426760, 0.16996515, 0.00000000, 0.00000000, 
0.34255550, 0.16155103, 0.00000000, 0.00000000, 
0.35042270, 0.15313692, 0.00000000, 0.00000000, 
0.35786920, 0.14472280, 0.00000000, 0.00000000, 
0.36489498, 0.13630868, 0.00000000, 0.00000000, 
0.37150006, 0.12789457, 0.00000000, 0.00000000, 
0.37768444, 0.11948045, 0.00000000, 0.00000000, 
0.38344811, 0.11106634, 0.00000000, 0.00000000, 
0.38879107, 0.10265222, 0.00000000, 0.00000000, 
0.39371333, 0.09423810, 0.00000000, 0.00000000, 
0.39821488, 0.08582399, 0.00000000, 0.00000000, 
0.40229573, 0.07740987, 0.00000000, 0.00000000, 
0.40595587, 0.06899575, 0.00000000, 0.00000000, 
0.40919531, 0.06058164, 0.00000000, 0.00000000, 
0.41201403, 0.05216752, 0.00000000, 0.00000000, 
0.41441206, 0.04375340, 0.00000000, 0.00000000, 
0.41638937, 0.03533929, 0.00000000, 0.00000000, 
0.41794599, 0.02692517, 0.00000000, 0.00000000, 
0.41908189, 0.01851106, 0.00000000, 0.00000000, 
0.41979709, 0.01009694, 0.00000000, 0.00000000, 
0.42009159, 0.00168282, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.41988965, -0.00841412, 0.00000000, 0.00000000, 
0.41925859, -0.01682823, 0.00000000, 0.00000000, 
0.41820682, -0.02524235, 0.00000000, 0.00000000, 
0.41673435, -0.03365647, 0.00000000, 0.00000000, 
0.41484118, -0.04207058, 0.00000000, 0.00000000, 
0.41252730, -0.05048470, 0.00000000, 0.00000000, 
0.40979271, -0.05889881, 0.00000000, 0.00000000, 
0.40663741, -0.06731293, 0.00000000, 0.00000000, 
0.40306141, -0.07572705, 0.00000000, 0.00000000, 
0.39906471, -0.08414116, 0.00000000, 0.00000000, 
0.39464730, -0.09255528, 0.00000000, 0.00000000, 
0.38980918, -0.10096940, 0.00000000, 0.00000000, 
0.38455036, -0.10938351, 0.00000000, 0.00000000, 
0.37887083, -0.11779763, 0.00000000, 0.00000000, 
0.37277060, -0.12621174, 0.00000000, 0.00000000, 
0.36624966, -0.13462586, 0.00000000, 0.00000000, 
0.35930801, -0.14303998, 0.00000000, 0.00000000, 
0.35194566, -0.15145409, 0.00000000, 0.00000000, 
0.34416260, -0.15986821, 0.00000000, 0.00000000, 
0.33595884, -0.16828233, 0.00000000, 0.00000000, 
0.32733437, -0.17669644, 0.00000000, 0.00000000, 
0.31828919, -0.18511056, 0.00000000, 0.00000000, 
0.30882331, -0.19352468, 0.00000000, 0.00000000, 
0.29893672, -0.20193879, 0.00000000, 0.00000000, 
0.28862943, -0.21035291, 0.00000000, 0.00000000, 
0.27790143, -0.21876702, 0.00000000, 0.00000000, 
0.26675273, -0.22718114, 0.00000000, 0.00000000, 
0.25518332, -0.23559526, 0.00000000, 0.00000000, 
0.24319320, -0.24400937, 0.00000000, 0.00000000, 
0.23078238, -0.25242349, 0.00000000, 0.00000000, 
0.21795086, -0.26083761, 0.00000000, 0.00000000, 
0.20476593, -0.26252043, 0.00000000, 0.00000000, 
0.19185027, -0.25410631, 0.00000000, 0.00000000, 
0.17935530, -0.24569220, 0.00000000, 0.00000000, 
0.16728105, -0.23727808, 0.00000000, 0.00000000, 
0.15562750, -0.22886396, 0.00000000, 0.00000000, 
0.14439465, -0.22044985, 0.00000000, 0.00000000, 
0.13358251, -0.21203573, 0.00000000, 0.00000000, 
0.12319108, -0.20362162, 0.00000000, 0.00000000, 
0.11322035, -0.19520750, 0.00000000, 0.00000000, 
0.10367033, -0.18679338, 0.00000000, 0.00000000, 
0.09454101, -0.17837927, 0.00000000, 0.00000000, 
0.08583240, -0.16996515, 0.00000000, 0.00000000, 
0.07754450, -0.16155103, 0.00000000, 0.00000000, 
0.06967730, -0.15313692, 0.00000000, 0.00000000, 
0.06223080, -0.14472280, 0.00000000, 0.00000000, 
0.05520502, -0.13630868, 0.00000000, 0.00000000, 
0.04859994, -0.12789457, 0.00000000, 0.00000000, 
0.04241556, -0.11948045, 0.00000000, 0.00000000, 
0.03665189, -0.11106634, 0.00000000, 0.00000000, 
0.03130893, -0.10265222, 0.00000000, 0.00000000, 
0.02638667, -0.09423810, 0.00000000, 0.00000000, 
0.02188512, -0.08582399, 0.00000000, 0.00000000, 
0.01780427, -0.07740987, 0.00000000, 0.00000000, 
0.01414413, -0.06899575, 0.00000000, 0.00000000, 
0.01090469, -0.06058164, 0.00000000, 0.00000000, 
0.00808597, -0.05216752, 0.00000000, 0.00000000, 
0.00568794, -0.04375340, 0.00000000, 0.00000000, 
0.00371063, -0.03533929, 0.00000000, 0.00000000, 
0.00215401, -0.02692517, 0.00000000, 0.00000000, 
0.00101811, -0.01851106, 0.00000000, 0.00000000, 
0.00030291, -0.01009694, 0.00000000, 0.00000000, 
0.00000841, -0.00168282, 0.00000000, 0.00000000}; 
