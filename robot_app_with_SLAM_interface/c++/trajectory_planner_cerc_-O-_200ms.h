double len=117; 
static double ref_profile[][4]={ 
0.00000000, 0.00000000, 0.00000000, 0.00000000, 
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
0.25695281, -0.00016273, 0.08231104, 0.02115005, 
0.25687958, -0.00056956, 0.24648264, 0.06331636, 
0.25672498, -0.00097638, 0.34973156, 0.08978483, 
0.25648903, -0.00138321, 0.40118225, 0.10289885, 
0.25617170, -0.00179003, 0.41566656, 0.10648201, 
0.25581878, -0.00158662, 0.40814795, 0.10441191, 
0.25554214, -0.00117979, 0.39046419, 0.09978005, 
0.25534686, -0.00077297, 0.37023936, 0.09453946, 
0.25523295, -0.00036614, 0.35180922, 0.08979331, 
0.25520000, 0.00000000, 0.33736923, 0.08609663, 
0.25520000, 0.00000000, 0.32785202, 0.08366784, 
0.25520000, 0.00000000, 0.32361631, 0.08258688, 
0.25520000, 0.00000000, 0.32478501, 0.08288513, 
0.25520000, 0.00000000, 0.33132747, 0.08455477, 
0.25520498, 0.00014239, 0.34303191, 0.08754345, 
0.25527414, 0.00054921, 0.35937112, 0.09173815, 
0.25542467, 0.00095604, 0.37894814, 0.09679270, 
0.25565656, 0.00136286, 0.39877652, 0.10194983, 
0.25596981, 0.00176969, 0.41324196, 0.10577747, 
0.25632457, 0.00160696, 0.41295198, 0.10584974, 
0.25660528, 0.00120013, 0.38442949, 0.09864663, 
0.25680462, 0.00079331, 0.31224645, 0.08018633, 
0.25692260, 0.00038648, 0.18322068, 0.04707353, 
0.25695931, 0.00000000, 0.00000000, 0.00000000, 
0.24427674, -0.12682575, 0.00000000, 0.00000000, 
0.20622901, -0.25365151, 0.00000000, 0.00000000, 
0.14281614, -0.38047726, 0.00000000, 0.00000000, 
0.07693016, -0.26633408, 0.00000000, 0.00000000, 
0.03634592, -0.13950833, 0.00000000, 0.00000000, 
0.02112683, -0.01268258, 0.00000000, 0.00000000, 
0.02100000, 0.00000000, 0.00000000, 0.00000000, 
0.02100000, 0.00000000, 0.00000000, 0.00000000, 
0.02100000, 0.00000000, 0.00000000, 0.00000000, 
0.02018449, -0.00959420, 0.00000000, 0.00000000, 
0.01713693, -0.02088148, 0.00000000, 0.00000000, 
0.01183190, -0.03216877, 0.00000000, 0.00000000, 
0.00571419, -0.02539640, 0.00000000, 0.00000000, 
0.00176364, -0.01410911, 0.00000000, 0.00000000, 
0.00007055, -0.00282182, 0.00000000, 0.00000000}; 
