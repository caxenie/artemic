int activate_params = 1;
double len=323; 
static double ref_profile[][4]={ 
0.00000000, 0.00000000, 0.00000000, 0.00000000, 
0.01207778, 0.12077778, 0.00000000, 0.00000000, 
0.04831111, 0.24155556, 0.00000000, 0.00000000, 
0.10870000, 0.36233333, 0.00000000, 0.00000000, 
0.16908889, 0.24155556, 0.00000000, 0.00000000, 
0.20532222, 0.12077778, 0.00000000, 0.00000000, 
0.21740000, 0.00000000, 0.00000000, 0.00000000, 
0.21740000, 0.00000000, 0.00000000, 0.00000000, 
0.21740000, 0.00000000, 0.00000000, 0.00000000, 
0.21740000, 0.00000000, 0.00000000, 0.00000000, 
0.21506733, -0.02591854, 0.00000000, 0.00000000, 
0.20700378, -0.05471692, 0.00000000, 0.00000000, 
0.19318056, -0.08351531, 0.00000000, 0.00000000, 
0.17826300, -0.06047660, 0.00000000, 0.00000000, 
0.16904752, -0.03167822, 0.00000000, 0.00000000, 
0.16559171, -0.00287984, 0.00000000, 0.00000000, 
0.16698983, 0.01678723, 0.15546720, 0.02596144, 
0.17232224, 0.03653691, 0.29806990, 0.05136407, 
0.18160459, 0.05628660, 0.40142846, 0.07290125, 
0.19482701, 0.07406131, 0.47045395, 0.09165713, 
0.20766430, 0.05431163, 0.50107769, 0.10405595, 
0.21655166, 0.03456195, 0.49707210, 0.10764179, 
0.22148908, 0.01481226, 0.47522029, 0.10525610, 
0.22260000, 0.00000000, 0.44887334, 0.09991921, 
0.22260000, 0.00000000, 0.43015939, 0.09575348, 
0.22260000, 0.00000000, 0.42316595, 0.09419674, 
0.22260000, 0.00000000, 0.42826981, 0.09533286, 
0.22253005, -0.00174879, 0.44506708, 0.09904080, 
0.22174309, -0.00612076, 0.47073601, 0.10438246, 
0.22008175, -0.01049273, 0.50018930, 0.11008253, 
0.21754600, -0.01486469, 0.52259946, 0.11368942, 
0.21445065, -0.01399030, 0.51895275, 0.11128975, 
0.21208979, -0.00961833, 0.46368895, 0.09834369, 
0.21060332, -0.00524636, 0.32464015, 0.06837029, 
0.20999124, -0.00087439, 0.07773753, 0.01632420, 
0.20993141, -0.00056451, -0.21486736, -0.04510741, 
0.20974324, -0.00131720, -0.40288756, -0.08450294, 
0.20940454, -0.00206988, -0.49014173, -0.10263790, 
0.20891529, -0.00282257, -0.50841904, -0.10621651, 
0.20841137, -0.00214515, -0.49086452, -0.10230175, 
0.20805761, -0.00139247, -0.46127139, -0.09597102, 
0.20785438, -0.00063978, -0.43261768, -0.08992148, 
0.20780000, -0.00000000, -0.41086926, -0.08537863, 
0.20780000, -0.00000000, -0.39817221, -0.08274019, 
0.20780000, -0.00000000, -0.39518828, -0.08212012, 
0.20780000, -0.00000000, -0.40204408, -0.08354476, 
0.20780677, 0.00022581, -0.41843198, -0.08695300, 
0.20792720, 0.00097849, -0.44334116, -0.09218269, 
0.20819817, 0.00173117, -0.47340355, -0.09856175, 
0.20861967, 0.00248386, -0.50034052, -0.10438088, 
0.20915408, 0.00248386, -0.50726398, -0.10609633, 
0.20957558, 0.00173117, -0.46592328, -0.09764614, 
0.20984655, 0.00097849, -0.34199236, -0.07176592, 
0.20996698, 0.00022581, -0.10932260, -0.02295414, 
0.20994195, -0.00048925, -0.18979248, -0.03984540, 
0.20976883, -0.00124193, -0.38904235, -0.08160896, 
0.20944518, -0.00199461, -0.48510505, -0.10160292, 
0.20897099, -0.00274730, -0.50870365, -0.10630430, 
0.20845502, -0.00222042, -0.49345781, -0.10286376, 
0.20808621, -0.00146774, -0.46433472, -0.09662165, 
0.20786793, -0.00071505, -0.43523295, -0.09047097, 
0.20780000, -0.00000000, -0.41265253, -0.08574920, 
0.20780000, -0.00000000, -0.39901074, -0.08291443, 
0.20780000, -0.00000000, -0.39504284, -0.08208990, 
0.20780000, -0.00000000, -0.40092034, -0.08331125, 
0.20780301, 0.00015054, -0.41638243, -0.08652552, 
0.20790839, 0.00090322, -0.44053450, -0.09159082, 
0.20816430, 0.00165591, -0.47034750, -0.09790956, 
0.20857075, 0.00240859, -0.49818239, -0.10390627, 
0.20910365, 0.00255913, -0.50819989, -0.10626645, 
0.20954021, 0.00180644, -0.47320801, -0.09915610, 
0.20982623, 0.00105376, -0.35900750, -0.07532919, 
0.20996171, 0.00030107, -0.13773143, -0.02891833, 
0.20995098, -0.00041398, 0.16357446, 0.03434262, 
0.20979292, -0.00116666, 0.37414674, 0.07849334, 
0.20948432, -0.00191935, 0.47934261, 0.10041476, 
0.20902518, -0.00267203, 0.50860569, 0.10631140, 
0.20850018, -0.00229569, 0.49592167, 0.10339976, 
0.20811632, -0.00154300, 0.46740429, 0.09727446, 
0.20788298, -0.00079032, 0.43791652, 0.09103539, 
0.20780019, -0.00003763, 0.41452549, 0.08613848, 
0.20780000, -0.00000000, 0.39994651, 0.08310889, 
0.20780000, -0.00000000, 0.39499615, 0.08208020, 
0.20780000, -0.00000000, 0.39989301, 0.08309777, 
0.20780075, 0.00007527, 0.41442226, 0.08611726, 
0.20789107, 0.00082795, 0.43778801, 0.09101222, 
0.20813193, 0.00158064, 0.46727839, 0.09725555, 
0.20852333, 0.00233332, 0.49585633, 0.10339761, 
0.20905171, 0.00263440, 0.50869172, 0.10634288, 
0.20950333, 0.00188171, 0.47969662, 0.10049804, 
0.20980440, 0.00112903, 0.37492754, 0.07866145, 
0.20995494, 0.00037634, 0.16482663, 0.03460617, 
0.20995851, -0.00033871, 0.13622935, 0.02860251, 
0.20981550, -0.00109139, 0.35817655, 0.07515099, 
0.20952195, -0.00184408, 0.47281823, 0.09906580, 
0.20907787, -0.00259676, 0.50809412, 0.10623124, 
0.20854685, -0.00237096, 0.49823688, 0.10390573, 
0.20814793, -0.00161827, 0.47047059, 0.09792748, 
0.20789954, -0.00086559, 0.44066438, 0.09161392, 
0.20780169, -0.00011290, 0.41648887, 0.08654709, 
0.20780000, -0.00000000, 0.40097912, 0.08332346, 
0.20780000, -0.00000000, 0.39504823, 0.08209102, 
0.20780000, -0.00000000, 0.39896252, 0.08290441, 
0.20780000, -0.00000000, 0.41255302, 0.08572852, 
0.20787527, 0.00075268, 0.43510609, 0.09044779, 
0.20810107, 0.00150537, 0.46420656, 0.09660188, 
0.20847742, 0.00225805, 0.49338264, 0.10285914, 
0.20899827, 0.00270966, 0.50877139, 0.10633234, 
0.20946494, 0.00195698, 0.48542495, 0.10167951, 
0.20978107, 0.00120430, 0.38977420, 0.08176725, 
0.20994666, 0.00045161, 0.19103644, 0.04010746, 
0.20996453, -0.00026344, 0.10777924, 0.02262982, 
0.20983658, -0.00101612, 0.34111035, 0.07157743, 
0.20955808, -0.00176881, 0.46549610, 0.09754847, 
0.20912905, -0.00252149, 0.50713699, 0.10605708, 
0.20859502, -0.00244623, 0.50038312, 0.10437743, 
0.20818105, -0.00169354, 0.47352321, 0.09857856, 
0.20791761, -0.00094086, 0.44347213, 0.09220566, 
0.20780470, -0.00018817, 0.41854153, 0.08697490, 
0.20780000, -0.00000000, 0.40210809, 0.08355806, 
0.20780000, -0.00000000, 0.39519904, 0.08212236, 
0.20780000, -0.00000000, 0.39812931, 0.08273127, 
0.20780000, -0.00000000, 0.41077465, 0.08535897, 
0.20786097, 0.00067742, 0.43249270, 0.08989835, 
0.20807172, 0.00143010, 0.46114151, 0.09595051, 
0.20843301, 0.00218279, 0.49078048, 0.10229485, 
0.20894333, 0.00278493, 0.50846990, 0.10624139, 
0.20942505, 0.00203225, 0.49042917, 0.10270815, 
0.20975623, 0.00127956, 0.40357166, 0.08465167, 
0.20993687, 0.00052688, 0.21608361, 0.04536392, 
0.20996905, -0.00018817, 0.07825285, 0.01643068, 
0.20985615, -0.00094086, 0.32292908, 0.06776865, 
0.20959271, -0.00169354, 0.45734086, 0.09585531, 
0.20917873, -0.00244623, 0.50570137, 0.10578197, 
0.20864470, -0.00252149, 0.50233879, 0.10481033, 
0.20821567, -0.00176881, 0.47655104, 0.09922539, 
0.20793718, -0.00101612, 0.44633494, 0.09280963, 
0.20780922, -0.00026344, 0.42068166, 0.08742153, 
0.20780000, -0.00000000, 0.40333289, 0.08381257, 
0.20780000, -0.00000000, 0.39544856, 0.08217421, 
0.20780000, -0.00000000, 0.39739370, 0.08257841, 
0.20780000, -0.00000000, 0.40908690, 0.08500826, 
0.20784817, 0.00060215, 0.42995147, 0.08936463, 
0.20804387, 0.00135483, 0.45809209, 0.09530325, 
0.20839010, 0.00210752, 0.48806788, 0.10170852, 
0.20888688, 0.00286020, 0.50781709, 0.10607633, 
0.20938365, 0.00210752, 0.49474548, 0.10359161, 
0.20972988, 0.00135483, 0.41634628, 0.08732026, 
0.20992558, 0.00060215, 0.23993622, 0.05036875, 
0.20997206, -0.00011290, 0.04768998, 0.01001356, 
0.20987421, -0.00086559, 0.30361705, 0.06372139, 
0.20962582, -0.00161827, 0.44831774, 0.09397898, 
0.20922690, -0.00237096, 0.50375352, 0.10539879, 
0.20869588, -0.00259676, 0.50408119, 0.10519967, 
0.20825180, -0.00184408, 0.47954202, 0.09986549, 
0.20795825, -0.00109139, 0.44924750, 0.09342472, 
0.20781524, -0.00033871, 0.42290733, 0.08788659, 
0.20780000, -0.00000000, 0.40465290, 0.08408687, 
0.20780000, -0.00000000, 0.39579667, 0.08224655, 
0.20780000, -0.00000000, 0.39675598, 0.08244589, 
0.20780000, -0.00000000, 0.40749097, 0.08467662, 
0.20783688, 0.00052688, 0.42748568, 0.08884729, 
0.20801753, 0.00127956, 0.45506636, 0.09466178, 
0.20834871, 0.00203225, 0.48526172, 0.10110365, 
0.20883043, 0.00278493, 0.50684547, 0.10584475, 
0.20934075, 0.00218279, 0.49841010, 0.10433754, 
0.20970203, 0.00143010, 0.42812632, 0.08977896, 
0.20991279, 0.00067742, 0.26264546, 0.05513264, 
0.20996517, -0.00171594, 0.00000000, 0.00000000, 
0.20619011, -0.03603469, 0.00000000, 0.00000000, 
0.19555130, -0.07035344, 0.00000000, 0.00000000, 
0.17806589, -0.10124032, 0.00000000, 0.00000000, 
0.16124971, -0.06692157, 0.00000000, 0.00000000, 
0.15129727, -0.03260281, 0.00000000, 0.00000000, 
0.14820000, 0.00000000, 0.00000000, 0.00000000, 
0.14820000, -0.00000000, 0.00000000, 0.00000000, 
0.14820000, -0.00000000, 0.00000000, 0.00000000, 
0.14820000, -0.00000000, 0.00000000, 0.00000000, 
0.14907056, 0.00916376, 0.00000000, 0.00000000, 
0.15186792, 0.01880982, 0.00000000, 0.00000000, 
0.15659449, 0.02845589, 0.00000000, 0.00000000, 
0.16150916, 0.01977443, 0.00000000, 0.00000000, 
0.16449944, 0.01012837, 0.00000000, 0.00000000, 
0.16556050, 0.00048230, 0.00000000, 0.00000000, 
0.16544308, -0.00133146, 0.00000000, 0.00000000, 
0.16502885, -0.00281085, 0.00000000, 0.00000000, 
0.16431874, -0.00429025, 0.00000000, 0.00000000, 
0.16355241, -0.00310673, 0.00000000, 0.00000000, 
0.16307901, -0.00162734, 0.00000000, 0.00000000, 
0.16290148, -0.00014794, 0.00000000, 0.00000000, 
0.16290000, -0.00000000, 0.00000000, 0.00000000, 
0.16290000, -0.00000000, 0.00000000, 0.00000000, 
0.16290000, -0.00000000, 0.00000000, 0.00000000, 
0.16299468, 0.00118352, 0.00000000, 0.00000000, 
0.16337932, 0.00266291, 0.00000000, 0.00000000, 
0.16405985, 0.00414231, 0.00000000, 0.00000000, 
0.16484689, 0.00325467, 0.00000000, 0.00000000, 
0.16534988, 0.00177528, 0.00000000, 0.00000000, 
0.16555700, 0.00029588, 0.00000000, 0.00000000, 
0.16667383, 0.01481226, 0.13886071, 0.02314445, 
0.17161125, 0.03456195, 0.28565603, 0.04902179, 
0.18049861, 0.05431163, 0.39272151, 0.07088569, 
0.19333591, 0.07406131, 0.46495817, 0.08989311, 
0.20655832, 0.05628660, 0.49984483, 0.10324711, 
0.21584067, 0.03653691, 0.49854236, 0.10760572, 
0.22117309, 0.01678723, 0.47778640, 0.10567349, 
0.22260000, 0.00000000, 0.45134455, 0.10046930, 
0.22260000, 0.00000000, 0.43151658, 0.09605559, 
0.22260000, 0.00000000, 0.42332179, 0.09423143, 
0.22260000, 0.00000000, 0.42721719, 0.09509855, 
0.22256065, -0.00131159, 0.44292764, 0.09857826, 
0.22186114, -0.00568356, 0.46788357, 0.10380518, 
0.22028723, -0.01005553, 0.49731943, 0.10955312, 
0.21783893, -0.01442750, 0.52116194, 0.11352936, 
0.21473483, -0.01442750, 0.52112703, 0.11190412, 
0.21228652, -0.01005553, 0.47246658, 0.10029829, 
0.21071262, -0.00568356, 0.34313120, 0.07230207, 
0.21001310, -0.00131159, 0.10836739, 0.02275857, 
0.20994195, -0.00048925, 0.18979248, 0.03984540, 
0.20976883, -0.00124193, 0.38904235, 0.08160896, 
0.20944518, -0.00199461, 0.48510505, 0.10160292, 
0.20897099, -0.00274730, 0.50870365, 0.10630430, 
0.20845502, -0.00222042, 0.49345781, 0.10286376, 
0.20808621, -0.00146774, 0.46433472, 0.09662165, 
0.20786793, -0.00071505, 0.43523295, 0.09047097, 
0.20780000, -0.00000000, 0.41265253, 0.08574920, 
0.20780000, -0.00000000, 0.39901074, 0.08291443, 
0.20780000, -0.00000000, 0.39504284, 0.08208990, 
0.20780000, -0.00000000, 0.40092034, 0.08331125, 
0.20780301, 0.00015054, 0.41638243, 0.08652552, 
0.20790839, 0.00090322, 0.44053450, 0.09159082, 
0.20816430, 0.00165591, 0.47034750, 0.09790956, 
0.20857075, 0.00240859, 0.49818239, 0.10390627, 
0.20910365, 0.00255913, 0.50819989, 0.10626645, 
0.20954021, 0.00180644, 0.47320801, 0.09915610, 
0.20982623, 0.00105376, 0.35900750, 0.07532919, 
0.20996171, 0.00030107, 0.13773143, 0.02891833, 
0.21063956, 0.01210565, 0.00000000, 0.00000000, 
0.21526172, 0.03411593, 0.00000000, 0.00000000, 
0.22428594, 0.05612621, 0.00000000, 0.00000000, 
0.23771221, 0.07813649, 0.00000000, 0.00000000, 
0.25554053, 0.10014677, 0.00000000, 0.00000000, 
0.27777091, 0.12215705, 0.00000000, 0.00000000, 
0.30330284, 0.12215705, 0.00000000, 0.00000000, 
0.32553322, 0.10014677, 0.00000000, 0.00000000, 
0.34336155, 0.07813649, 0.00000000, 0.00000000, 
0.35678782, 0.05612621, 0.00000000, 0.00000000, 
0.36581203, 0.03411593, 0.00000000, 0.00000000, 
0.37043419, 0.01210565, 0.00000000, 0.00000000, 
0.37110000, 0.00000000, 0.00000000, 0.00000000, 
0.37110000, 0.00000000, 0.00000000, 0.00000000, 
0.37110000, 0.00000000, 0.00000000, 0.00000000, 
0.37110000, 0.00000000, 0.00000000, 0.00000000, 
0.37110000, 0.00000000, -0.00000000, -0.00000000, 
0.37110000, 0.00000000, -0.00000000, -0.00000000, 
0.37096536, -0.00269278, -0.00000000, -0.00000000, 
0.36988825, -0.00807835, -0.00000000, -0.00000000, 
0.36773402, -0.01346392, -0.00000000, -0.00000000, 
0.36450268, -0.01884948, -0.00000000, -0.00000000, 
0.36019423, -0.02423505, -0.00000000, -0.00000000, 
0.35480866, -0.02962062, -0.00000000, -0.00000000, 
0.34856410, -0.03015917, -0.00000000, -0.00000000, 
0.34307082, -0.02477361, -0.00000000, -0.00000000, 
0.33865465, -0.01938804, -0.00000000, -0.00000000, 
0.33531560, -0.01400247, -0.00000000, -0.00000000, 
0.33305366, -0.00861691, -0.00000000, -0.00000000, 
0.33186884, -0.00323134, -0.00000000, -0.00000000, 
0.33015341, -0.04347291, 0.00000000, 0.00000000, 
0.30903799, -0.16768122, 0.00000000, 0.00000000, 
0.26308092, -0.29188953, 0.00000000, 0.00000000, 
0.19532529, -0.32915202, 0.00000000, 0.00000000, 
0.14191571, -0.20494371, 0.00000000, 0.00000000, 
0.11334780, -0.08073540, 0.00000000, 0.00000000, 
0.10810000, 0.00000000, -0.00000000, -0.00000000, 
0.10810000, 0.00000000, -0.00000000, -0.00000000, 
0.10810000, 0.00000000, -0.00000000, -0.00000000, 
0.10829952, 0.00798096, -0.00000000, -0.00000000, 
0.11308810, 0.03990480, -0.00000000, -0.00000000, 
0.12426144, 0.07182864, -0.00000000, -0.00000000, 
0.14142051, 0.08779056, -0.00000000, -0.00000000, 
0.15578624, 0.05586672, -0.00000000, -0.00000000, 
0.16376720, 0.02394288, -0.00000000, -0.00000000, 
0.16564191, 0.00394994, 0.03951219, 0.00654488, 
0.16840687, 0.02369962, 0.21014904, 0.03539054, 
0.17512176, 0.04344930, 0.33846200, 0.05927206, 
0.18578659, 0.06319899, 0.42922649, 0.07974453, 
0.19976937, 0.06714892, 0.48607963, 0.09710382, 
0.21122418, 0.04739924, 0.50274943, 0.10619284, 
0.21872906, 0.02764956, 0.49065557, 0.10732063, 
0.22228401, 0.00789987, 0.46596955, 0.10357758, 
0.22260000, 0.00000000, 0.44105164, 0.09817809, 
0.22260000, 0.00000000, 0.42634352, 0.09490407, 
0.22260000, 0.00000000, 0.42357641, 0.09428811, 
0.22260000, 0.00000000, 0.43288775, 0.09636081, 
0.22235408, -0.00327898, 0.45323055, 0.10077766, 
0.22126108, -0.00765095, 0.48100716, 0.10642817, 
0.21929370, -0.01202291, 0.50963810, 0.11176042, 
0.21645192, -0.01639488, 0.52541073, 0.11372616, 
0.21352489, -0.01246011, 0.50712079, 0.10828291, 
0.21147006, -0.00808814, 0.42610873, 0.09010924, 
0.21028963, -0.00371617, 0.25123270, 0.05283163, 
0.20998114, 0.00073895, -0.03203541, -0.00672683, 
0.21086788, 0.00812841, -0.29526467, -0.06226184, 
0.21323251, 0.01551788, -0.45227743, -0.09644025, 
0.21707503, 0.02290735, -0.52237122, -0.11339375, 
0.22239545, 0.03029681, -0.53651661, -0.11931885, 
0.22824790, 0.02586313, -0.52171922, -0.11908132, 
0.23268158, 0.01847367, -0.49537107, -0.11526373, 
0.23563737, 0.01108420, -0.47100565, -0.11098653, 
0.23711526, 0.00369473, -0.45535334, -0.10797123, 
0.23730000, 0.00000000, -0.45137967, -0.10711240, 
0.23730000, 0.00000000, -0.46168371, -0.10955754, 
0.23730000, 0.00000000, -0.48593177, -0.11531161, 
0.23730000, 0.00000000, -0.52121770, -0.12368496, 
0.23715562, -0.00962547, -0.55845561, -0.13244089, 
0.22881354, -0.07379529, -0.55699338, -0.12744763, 
0.20763750, -0.13796512, -0.47717859, -0.09908017, 
0.17362749, -0.20213494, -0.32433912, -0.05631419, 
0.12678352, -0.26630476, -0.15780695, -0.02000732, 
0.07637813, -0.22138588, -0.05154792, -0.00393713, 
0.03851794, -0.15721606, -0.01148985, -0.00044257, 
0.01349170, -0.09304624, -0.00194858, -0.00002629, 
0.00129944, -0.02887642, -0.00015207, -0.00000020}; 