


double len=306; 
static double ref_profile[][4]={ 
0.00000000, 0.00000000, 0.00000000, 0.00000000,/*first line*/
0.00336565, 0.03365647, 0.00000000, 0.00000000, 
0.01346259, 0.06731293, 0.00000000, 0.00000000, 
0.03029082, 0.10096940, 0.00000000, 0.00000000, 
0.05385034, 0.13462586, 0.00000000, 0.00000000, 
0.08414116, 0.16828233, 0.00000000, 0.00000000, 
0.12116328, 0.20193879, 0.00000000, 0.00000000, 
0.16491668, 0.23559526, 0.00000000, 0.00000000, 
0.21533407, 0.26252043, 0.00000000, 0.00000000, 
0.26447250, 0.22886396, 0.00000000, 0.00000000, 
0.30687965, 0.19520750, 0.00000000, 0.00000000, 
0.34255550, 0.16155103, 0.00000000, 0.00000000, 
0.37150006, 0.12789457, 0.00000000, 0.00000000, 
0.39371333, 0.09423810, 0.00000000, 0.00000000, 
0.40919531, 0.06058164, 0.00000000, 0.00000000, 
0.41794599, 0.02692517, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.41988965, -0.00841412, 0.00000000, 0.00000000, 
0.41484118, -0.04207058, 0.00000000, 0.00000000, 
0.40306141, -0.07572705, 0.00000000, 0.00000000,
0.14439465, -0.22044985, 0.00000000, 0.00000000, 
0.10367033, -0.18679338, 0.00000000, 0.00000000, 
0.06967730, -0.15313692, 0.00000000, 0.00000000, 
0.04241556, -0.11948045, 0.00000000, 0.00000000, 
0.02188512, -0.08582399, 0.00000000, 0.00000000,  
0.00808597, -0.05216752, 0.00000000, 0.00000000, 
0.00101811, -0.01851106, 0.00000000, 0.00000000,
0.00000000, 0.00000000, 0.0000000, 0.00000000,// first circle
0.02540466, 0.25404664, 0.00000000, 0.00000000, 
0.08015171, 0.17783265, 0.00000000, 0.00000000, 
0.09260000, 0.00000000, 0.00000000, 0.00000000, 
0.09260000, 0.00000000, 0.00000000, 0.00000000, 
0.08801299, -0.04828431, 0.00000000, 0.00000000, 
0.07693301, -0.03811919, 0.00000000, 0.00000000, 
0.07427514, 0.01005321, 0.00358434, 0.00026623, 
0.08131238, 0.06031925, 0.02339328, 0.00190216, 
0.09840284, 0.11058529, 0.05311616, 0.00522678, 
0.12554650, 0.16085134, 0.10224407, 0.01283639, 
0.16274337, 0.21111738, 0.17928246, 0.02917703, 
0.20838494, 0.22117059, 0.28483892, 0.05935614, 
0.24759245, 0.17090455, 0.38436398, 0.09516562, 
0.27674676, 0.12063850, 0.44887339, 0.12422426, 
0.29584786, 0.07037246, 0.47112393, 0.13938100, 
0.30489574, 0.02010642, 0.46036839, 0.14036436, 
0.30570000, 0.00000000, 0.43340142, 0.13249081, 
0.30570000, 0.00000000, 0.40991019, 0.12530954, 
0.30570000, 0.00000000, 0.39427000, 0.12052834, 
0.30570000, 0.00000000, 0.38761340, 0.11849342, 
0.30570000, 0.00000000, 0.39023914, 0.11929610, 
0.30493578, -0.00899079, 0.40102467, 0.12228677, 
0.30207988, -0.01956820, 0.41717030, 0.12601875, 
0.29710850, -0.03014561, 0.43572137, 0.12945652, 
0.29002164, -0.04072301, 0.45098510, 0.13079544, 
0.28082459, -0.05024268, 0.45379944, 0.12743804, 
0.27183379, -0.03966527, 0.43602922, 0.11852748, 
0.26495848, -0.02908787, 0.38770338, 0.10272530, 
0.26019865, -0.01851046, 0.29576911, 0.07695872, 
0.25755429, -0.00793305, 0.15006985, 0.03865113, 
0.25695769, -0.00008137, 0.04223859, 0.01085353, 
0.25690073, -0.00048819, 0.21863178, 0.05616666, 
0.25676241, -0.00089502, 0.33364283, 0.08566694, 
0.25654273, -0.00130184, 0.39435435, 0.10116874, 
0.25624168, -0.00170867, 0.41497891, 0.10633489, 
0.25588387, -0.00166798, 0.41077922, 0.10511178, 
0.25559096, -0.00126116, 0.39439353, 0.10080342, 
0.25537941, -0.00085433, 0.37424166, 0.09557361, 
0.25524923, -0.00044751, 0.35522401, 0.09067065, 
0.25520041, -0.00004068, 0.33987922, 0.08673732, 
0.25520000, 0.00000000, 0.32934044, 0.08404768, 
0.25520000, 0.00000000, 0.32403251, 0.08269310, 
0.25520000, 0.00000000, 0.32411837, 0.08271501, 
0.25520000, 0.00000000, 0.32959576, 0.08411284, 
0.25520092, 0.00006102, 0.34029549, 0.08684372, 
0.25525380, 0.00046785, 0.35578203, 0.09081472, 
0.25538805, 0.00087467, 0.37488668, 0.09574158, 
0.25560367, 0.00128150, 0.39501277, 0.10096671, 
0.25590065, 0.00168832, 0.41116558, 0.10521754, 
0.25625866, 0.00168832, 0.41479195, 0.10629403, 
0.25655564, 0.00128150, 0.39313106, 0.10085999, 
0.25677126, 0.00087467, 0.33088758, 0.08496242, 
0.25690551, 0.00046785, 0.21396798, 0.05496955, 
0.25695840, 0.00006102, 0.03629431, 0.00932613, 
0.25693328, -0.00032546, 0.15541149, 0.03993038, 
0.25682750, -0.00073229, 0.29479087, 0.07571040, 
0.25664036, -0.00113911, 0.37575425, 0.09643371, 
0.25637186, -0.00154594, 0.41053197, 0.10524884, 
0.25602382, -0.00183071, 0.41453707, 0.10613137, 
0.25569836, -0.00142389, 0.40178041, 0.10273459, 
0.25545427, -0.00101706, 0.38237534, 0.09767941, 
0.25529154, -0.00061024, 0.36249265, 0.09254131, 
0.25521017, -0.00020341, 0.34548000, 0.08817001, 
0.25520000, 0.00000000, 0.33294542, 0.08496767, 
0.25520000, 0.00000000, 0.32551295, 0.08307090, 
0.25520000, 0.00000000, 0.32343390, 0.08254033, 
0.25520000, 0.00000000, 0.32676383, 0.08339013, 
0.25520000, 0.00000000, 0.33540999, 0.08559663, 
0.25522288, 0.00030512, 0.34906344, 0.08908898, 
0.25532459, 0.00071194, 0.36693534, 0.09368762, 
0.25550766, 0.00111877, 0.38709206, 0.09890499, 
0.25577210, 0.00152559, 0.40563599, 0.10375037, 
0.25611709, 0.00185105, 0.41557657, 0.10643626, 
0.25644661, 0.00144423, 0.40578365, 0.10406184, 
0.25669478, 0.00103740, 0.36164469, 0.09283230, 
0.25686158, 0.00063058, 0.26798258, 0.06883443, 
0.25694701, 0.00022375, 0.11431276, 0.02937232, 
0.25707425, 0.00287350, 0.08688230, 0.02233520, 
0.25836733, 0.01005724, 0.27116923, 0.07006127, 
0.26109715, 0.01724099, 0.41247520, 0.10769610, 
0.26526372, 0.02442473, 0.50968874, 0.13520193, 
0.27086704, 0.03160847, 0.56018207, 0.15173486, 
0.27773111, 0.03376360, 0.56700990, 0.15747629, 
0.28376545, 0.02657985, 0.53788714, 0.15263379, 
0.28836305, 0.01939611, 0.48856562, 0.14088427, 
0.29152390, 0.01221236, 0.43362421, 0.12641182, 
0.29324800, 0.00502862, 0.38179542, 0.11196074, 
0.29360000, 0.00000000, 0.33687209, 0.09890564, 
0.29360000, -0.00000000, 0.30052899, 0.08823531, 
0.29360000, -0.00000000, 0.27194780, 0.07984387, 
0.29360000, -0.00000000, 0.24948371, 0.07324842, 
0.29360000, -0.00000000, 0.23127766, 0.06790312, 
0.29347048, -0.00863445, 0.21494407, 0.06307974, 
0.28598730, -0.06619743, 0.19259566, 0.05507991, 
0.26699151, -0.12376042, 0.15974262, 0.04264992, 
0.23648313, -0.18132340, 0.11740923, 0.02776530, 
0.19446215, -0.23888638, 0.07191587, 0.01398492, 
0.14104370, -0.28493677, 0.03385337, 0.00477480, 
0.08981265, -0.22737379, 0.01226097, 0.00110119, 
0.05009419, -0.16981080, 0.00343422, 0.00017203, 
0.02188832, -0.11224782, 0.00076016, 0.00001664, 
0.00519506, -0.05468483, 0.00008711, 0.00000045,
0.00000000, 0.00000000, 0.0000000, 0.0000000,/*second line*/
0.00336565, 0.03365647, 0.00000000, 0.00000000, 
0.01346259, 0.06731293, 0.00000000, 0.00000000, 
0.03029082, 0.10096940, 0.00000000, 0.00000000, 
0.05385034, 0.13462586, 0.00000000, 0.00000000, 
0.08414116, 0.16828233, 0.00000000, 0.00000000, 
0.12116328, 0.20193879, 0.00000000, 0.00000000, 
0.16491668, 0.23559526, 0.00000000, 0.00000000, 
0.21533407, 0.26252043, 0.00000000, 0.00000000, 
0.26447250, 0.22886396, 0.00000000, 0.00000000, 
0.30687965, 0.19520750, 0.00000000, 0.00000000, 
0.34255550, 0.16155103, 0.00000000, 0.00000000, 
0.37150006, 0.12789457, 0.00000000, 0.00000000, 
0.39371333, 0.09423810, 0.00000000, 0.00000000, 
0.40919531, 0.06058164, 0.00000000, 0.00000000, 
0.41794599, 0.02692517, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.41988965, -0.00841412, 0.00000000, 0.00000000, 
0.41484118, -0.04207058, 0.00000000, 0.00000000, 
0.40306141, -0.07572705, 0.00000000, 0.00000000, 
0.38455036, -0.10938351, 0.00000000, 0.00000000, 
0.35930801, -0.14303998, 0.00000000, 0.00000000, 
0.32733437, -0.17669644, 0.00000000, 0.00000000, 
0.28862943, -0.21035291, 0.00000000, 0.00000000, 
0.24319320, -0.24400937, 0.00000000, 0.00000000, 
0.19185027, -0.25410631, 0.00000000, 0.00000000, 
0.14439465, -0.22044985, 0.00000000, 0.00000000, 
0.10367033, -0.18679338, 0.00000000, 0.00000000, 
0.06967730, -0.15313692, 0.00000000, 0.00000000, 
0.04241556, -0.11948045, 0.00000000, 0.00000000, 
0.02188512, -0.08582399, 0.00000000, 0.00000000, 
0.00808597, -0.05216752, 0.00000000, 0.00000000, 
0.00101811, -0.01851106, 0.00000000, 0.00000000,
0.00000000, 0.00000000, 0.00000000, 0.00000000, /* the turnaround */
0.00519758, 0.05197579, 0.00031694, 0.00000165, 
0.02079032, 0.10395158, 0.00092899, 0.00001931, 
0.04677821, 0.15592738, 0.00701477, 0.00032814, 
0.08316127, 0.20790317, 0.02861621, 0.00237976, 
0.12993948, 0.25987896, 0.08226327, 0.01068925, 
0.18201922, 0.23908864, 0.17948903, 0.03267045, 
0.22463937, 0.18711285, 0.29538806, 0.06635579, 
0.25686436, 0.13513706, 0.39439973, 0.10130724, 
0.27869420, 0.08316127, 0.45157326, 0.12585085, 
0.29012887, 0.03118548, 0.46364413, 0.13451655, 
0.29200000, 0.00000000, 0.44412605, 0.12968481, 
0.29200000, 0.00000000, 0.41819379, 0.12211259, 
0.29200000, 0.00000000, 0.39565350, 0.11553082, 
0.29200000, -0.00000000, 0.37959238, 0.11084098, 
0.29200000, -0.00000000, 0.37121307, 0.10839422, 
0.29197505, -0.00124744, 0.37085990, 0.10828184, 
0.29110184, -0.00748466, 0.37746040, 0.10987942, 
0.28898119, -0.01372188, 0.38990217, 0.11267439, 
0.28561309, -0.01995909, 0.40655868, 0.11611848, 
0.28099755, -0.02619631, 0.42409398, 0.11916937, 
0.27513457, -0.03243353, 0.43658032, 0.12011834, 
0.26903457, -0.02744375, 0.43661272, 0.11746391, 
0.26416954, -0.02120654, 0.41477341, 0.10957050, 
0.26055195, -0.01496932, 0.35716588, 0.09306027, 
0.25818181, -0.00873210, 0.25036287, 0.06463914, 
0.25705911, -0.00249489, 0.08575558, 0.02204425, 
0.25714799, 0.00343047, 0.11096650, 0.02853481, 
0.25845781, 0.00966769, 0.26779231, 0.06921301, 
0.26101507, 0.01590490, 0.36746727, 0.09591449, 
0.26481977, 0.02214212, 0.41954895, 0.11110485, 
0.26987191, 0.02837934, 0.43774159, 0.11813416, 
0.27609354, 0.03149795, 0.43565814, 0.12028240, 
0.28176940, 0.02526073, 0.42199345, 0.11890484, 
0.28619783, 0.01902351, 0.40425701, 0.11569748, 
0.28937881, 0.01278629, 0.38798591, 0.11227490, 
0.29131235, 0.00654908, 0.37623570, 0.10960211, 
0.29199844, 0.00031186, 0.37046009, 0.10817377, 
0.29200000, 0.00000000, 0.37187574, 0.10858772, 
0.29200000, 0.00000000, 0.38132305, 0.11134633, 
0.29200000, 0.00000000, 0.39835460, 0.11631954, 
0.29200000, 0.00000000, 0.42159122, 0.12310464, 
0.29200000, 0.00000000, 0.44756987, 0.13069040, 
0.28907636, -0.03898184, 0.46408913, 0.13415720, 
0.27608241, -0.09095764, 0.44620649, 0.12318976, 
0.25269331, -0.14293343, 0.38260472, 0.09668165, 
0.21890904, -0.19490922, 0.27957228, 0.06120090, 
0.17472962, -0.24688501, 0.16447297, 0.02873830, 
0.12226006, -0.25208259, 0.07285321, 0.00890704, 
0.07704112, -0.20010680, 0.02478338, 0.00190934, 
0.04221734, -0.14813101, 0.00617389, 0.00026065, 
0.01778871, -0.09615522, 0.00132299, 0.00002353, 
0.00375525, -0.04417942, 0.00003980, 0.00000015,
0.00000000, 0.00000000, 0.00000000, 0.00000000,/*third line begin*/
0.00336565, 0.03365647, 0.00000000, 0.00000000, 
0.01346259, 0.06731293, 0.00000000, 0.00000000, 
0.03029082, 0.10096940, 0.00000000, 0.00000000, 
0.05385034, 0.13462586, 0.00000000, 0.00000000, 
0.08414116, 0.16828233, 0.00000000, 0.00000000, 
0.12116328, 0.20193879, 0.00000000, 0.00000000, 
0.16491668, 0.23559526, 0.00000000, 0.00000000, 
0.21533407, 0.26252043, 0.00000000, 0.00000000, 
0.26447250, 0.22886396, 0.00000000, 0.00000000, 
0.30687965, 0.19520750, 0.00000000, 0.00000000, 
0.34255550, 0.16155103, 0.00000000, 0.00000000, 
0.37150006, 0.12789457, 0.00000000, 0.00000000, 
0.39371333, 0.09423810, 0.00000000, 0.00000000, 
0.40919531, 0.06058164, 0.00000000, 0.00000000, 
0.41794599, 0.02692517, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.41988965, -0.00841412, 0.00000000, 0.00000000, 
0.41484118, -0.04207058, 0.00000000, 0.00000000, 
0.40306141, -0.07572705, 0.00000000, 0.00000000, 
0.38455036, -0.10938351, 0.00000000, 0.00000000, 
0.35930801, -0.14303998, 0.00000000, 0.00000000, 
0.32733437, -0.17669644, 0.00000000, 0.00000000, 
0.28862943, -0.21035291, 0.00000000, 0.00000000, 
0.24319320, -0.24400937, 0.00000000, 0.00000000, 
0.19185027, -0.25410631, 0.00000000, 0.00000000, 
0.14439465, -0.22044985, 0.00000000, 0.00000000, 
0.10367033, -0.18679338, 0.00000000, 0.00000000, 
0.06967730, -0.15313692, 0.00000000, 0.00000000, 
0.04241556, -0.11948045, 0.00000000, 0.00000000, 
0.02188512, -0.08582399, 0.00000000, 0.00000000, 
0.00808597, -0.05216752, 0.00000000, 0.00000000, 
0.00101811, -0.01851106, 0.00000000, 0.00000000,
0.00101811, -0.01851106, 0.00000000, 0.00000000,
0.00000000, 0.00000000, 0.00000000, 0.00000000,/*fourth line begin*/
0.00336565, 0.03365647, 0.00000000, 0.00000000, 
0.01346259, 0.06731293, 0.00000000, 0.00000000, 
0.03029082, 0.10096940, 0.00000000, 0.00000000, 
0.05385034, 0.13462586, 0.00000000, 0.00000000, 
0.08414116, 0.16828233, 0.00000000, 0.00000000, 
0.12116328, 0.20193879, 0.00000000, 0.00000000, 
0.16491668, 0.23559526, 0.00000000, 0.00000000, 
0.21533407, 0.26252043, 0.00000000, 0.00000000, 
0.26447250, 0.22886396, 0.00000000, 0.00000000, 
0.30687965, 0.19520750, 0.00000000, 0.00000000, 
0.34255550, 0.16155103, 0.00000000, 0.00000000, 
0.37150006, 0.12789457, 0.00000000, 0.00000000, 
0.39371333, 0.09423810, 0.00000000, 0.00000000, 
0.40919531, 0.06058164, 0.00000000, 0.00000000, 
0.41794599, 0.02692517, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.42010000, 0.00000000, 0.00000000, 0.00000000, 
0.41988965, -0.00841412, 0.00000000, 0.00000000, 
0.41484118, -0.04207058, 0.00000000, 0.00000000, 
0.40306141, -0.07572705, 0.00000000, 0.00000000, 
0.38455036, -0.10938351, 0.00000000, 0.00000000, 
0.35930801, -0.14303998, 0.00000000, 0.00000000, 
0.32733437, -0.17669644, 0.00000000, 0.00000000, 
0.28862943, -0.21035291, 0.00000000, 0.00000000, 
0.24319320, -0.24400937, 0.00000000, 0.00000000, 
0.19185027, -0.25410631, 0.00000000, 0.00000000, 
0.14439465, -0.22044985, 0.00000000, 0.00000000, 
0.10367033, -0.18679338, 0.00000000, 0.00000000, 
0.06967730, -0.15313692, 0.00000000, 0.00000000, 
0.04241556, -0.11948045, 0.00000000, 0.00000000, 
0.02188512, -0.08582399, 0.00000000, 0.00000000, 
0.00808597, -0.05216752, 0.00000000, 0.00000000, 
0.00101811, -0.01851106, 0.00000000, 0.00000000};// THE END 
  
 