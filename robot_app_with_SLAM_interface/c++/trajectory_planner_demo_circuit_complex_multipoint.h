

double len=407; 
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
0.20578967, -0.07607416, 0.00000000, 0.00000000, 
0.17674318, -0.21439082, 0.00000000, 0.00000000, 
0.12445948, -0.24205416, 0.00000000, 0.00000000, 
0.08988031, -0.10373750, 0.00000000, 0.00000000, 
0.08210000, -0.00000000, -0.00000000, -0.00000000, 
0.08210000, -0.00000000, -0.00000000, -0.00000000, 
0.08225261, 0.00763026, -0.00000000, -0.00000000, 
0.08759379, 0.04578158, -0.00000000, -0.00000000, 
0.10054616, 0.08011776, -0.00000000, -0.00000000, 
0.11275458, 0.04196645, -0.00000000, -0.00000000, 
0.11733274, 0.00381513, -0.00000000, -0.00000000, 
0.11706838, -0.00355896, 0.00000000, 0.00000000, 
0.11593789, -0.00774597, 0.00000000, 0.00000000, 
0.11438032, -0.00607117, 0.00000000, 0.00000000, 
0.11358479, -0.00188416, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11360468, 0.00209351, -0.00000000, -0.00000000, 
0.11444208, 0.00628052, -0.00000000, -0.00000000, 
0.11601430, 0.00753662, -0.00000000, -0.00000000, 
0.11710292, 0.00334961, -0.00000000, -0.00000000, 
0.11736147, -0.00062805, 0.00000000, 0.00000000, 
0.11681716, -0.00481506, 0.00000000, 0.00000000, 
0.11543545, -0.00900207, 0.00000000, 0.00000000, 
0.11405373, -0.00481506, 0.00000000, 0.00000000, 
0.11350942, -0.00062805, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11376797, 0.00334961, -0.00000000, -0.00000000, 
0.11485659, 0.00753662, -0.00000000, -0.00000000, 
0.11642881, 0.00628052, -0.00000000, -0.00000000, 
0.11726622, 0.00209351, -0.00000000, -0.00000000, 
0.11728611, -0.00188416, 0.00000000, 0.00000000, 
0.11649057, -0.00607117, 0.00000000, 0.00000000, 
0.11493300, -0.00774597, 0.00000000, 0.00000000, 
0.11380251, -0.00355896, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11350419, 0.00041870, -0.00000000, -0.00000000, 
0.11400663, 0.00460571, -0.00000000, -0.00000000, 
0.11534647, 0.00879272, -0.00000000, -0.00000000, 
0.11676796, 0.00502441, -0.00000000, -0.00000000, 
0.11735414, 0.00083740, -0.00000000, -0.00000000, 
0.11713537, -0.00314026, 0.00000000, 0.00000000, 
0.11608862, -0.00732727, 0.00000000, 0.00000000, 
0.11450593, -0.00648987, 0.00000000, 0.00000000, 
0.11362666, -0.00230286, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11356699, 0.00167480, -0.00000000, -0.00000000, 
0.11432065, 0.00586182, -0.00000000, -0.00000000, 
0.11585938, 0.00795532, -0.00000000, -0.00000000, 
0.11703174, 0.00376831, -0.00000000, -0.00000000, 
0.11736985, -0.00020935, 0.00000000, 0.00000000, 
0.11690927, -0.00439636, 0.00000000, 0.00000000, 
0.11561130, -0.00858337, 0.00000000, 0.00000000, 
0.11415422, -0.00523376, 0.00000000, 0.00000000, 
0.11352617, -0.00104675, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11370516, 0.00293091, -0.00000000, -0.00000000, 
0.11471005, 0.00711792, -0.00000000, -0.00000000, 
0.11629902, 0.00669922, -0.00000000, -0.00000000, 
0.11722016, 0.00251221, -0.00000000, -0.00000000, 
0.11731960, -0.00146545, 0.00000000, 0.00000000, 
0.11660781, -0.00565247, 0.00000000, 0.00000000, 
0.11509211, -0.00816467, 0.00000000, 0.00000000, 
0.11387788, -0.00397766, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11391870, 0.00418701, -0.00000000, -0.00000000, 
0.11517480, 0.00837402, -0.00000000, -0.00000000, 
0.11666329, 0.00544311, -0.00000000, -0.00000000, 
0.11733321, 0.00125610, -0.00000000, -0.00000000, 
0.11719399, -0.00272156, 0.00000000, 0.00000000, 
0.11623098, -0.00690857, 0.00000000, 0.00000000, 
0.11463991, -0.00690857, 0.00000000, 0.00000000, 
0.11367690, -0.00272156, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11353768, 0.00125610, -0.00000000, -0.00000000, 
0.11420760, 0.00544311, -0.00000000, -0.00000000, 
0.11569609, 0.00837402, -0.00000000, -0.00000000, 
0.11695219, 0.00418701, -0.00000000, -0.00000000, 
0.11737089, 0.00000000, 0.00000000, 0.00000000, 
0.11699301, -0.00397766, 0.00000000, 0.00000000, 
0.11577878, -0.00816467, 0.00000000, 0.00000000, 
0.11426308, -0.00565247, 0.00000000, 0.00000000, 
0.11355129, -0.00146545, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11365073, 0.00251221, -0.00000000, -0.00000000, 
0.11457187, 0.00669922, -0.00000000, -0.00000000, 
0.11616085, 0.00711792, -0.00000000, -0.00000000, 
0.11716573, 0.00293091, -0.00000000, -0.00000000, 
0.11734472, -0.00104675, 0.00000000, 0.00000000, 
0.11671667, -0.00523376, 0.00000000, 0.00000000, 
0.11525959, -0.00858337, 0.00000000, 0.00000000, 
0.11396162, -0.00439636, 0.00000000, 0.00000000, 
0.11350105, -0.00020935, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11383915, 0.00376831, -0.00000000, -0.00000000, 
0.11501151, 0.00795532, -0.00000000, -0.00000000, 
0.11655024, 0.00586182, -0.00000000, -0.00000000, 
0.11730390, 0.00167480, -0.00000000, -0.00000000, 
0.11724423, -0.00230286, 0.00000000, 0.00000000, 
0.11636496, -0.00648987, 0.00000000, 0.00000000, 
0.11478227, -0.00732727, 0.00000000, 0.00000000, 
0.11373552, -0.00314026, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11351675, 0.00083740, -0.00000000, -0.00000000, 
0.11410293, 0.00502441, -0.00000000, -0.00000000, 
0.11552442, 0.00879272, -0.00000000, -0.00000000, 
0.11686426, 0.00460571, -0.00000000, -0.00000000, 
0.11736671, 0.00041870, -0.00000000, -0.00000000, 
0.11706838, -0.00355896, 0.00000000, 0.00000000, 
0.11593789, -0.00774597, 0.00000000, 0.00000000, 
0.11438032, -0.00607117, 0.00000000, 0.00000000, 
0.11358479, -0.00188416, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11360468, 0.00209351, -0.00000000, -0.00000000, 
0.11444208, 0.00628052, -0.00000000, -0.00000000, 
0.11601430, 0.00753662, -0.00000000, -0.00000000, 
0.11710292, 0.00334961, -0.00000000, -0.00000000, 
0.11746534, 0.00629653, 0.01506595, 0.00176973, 
0.12292233, 0.04827336, 0.11157414, 0.01371495, 
0.13677469, 0.09025020, 0.21269439, 0.02909121, 
0.15902241, 0.13222704, 0.32594462, 0.05183250, 
0.18863707, 0.14482009, 0.44353390, 0.08366693, 
0.21340340, 0.10284325, 0.51929654, 0.11081965, 
0.22977437, 0.06086642, 0.53894902, 0.12383667, 
0.23774997, 0.01888958, 0.52014789, 0.12366514, 
0.23860000, 0.00000000, 0.48682440, 0.11615630, 
0.23860000, -0.00000000, 0.46312105, 0.11050068, 
0.23860000, -0.00000000, 0.45367834, 0.10824765, 
0.23860000, -0.00000000, 0.45912007, 0.10954605, 
0.23811431, -0.00693849, 0.47812811, 0.11384914, 
0.23573539, -0.01685063, 0.50532396, 0.11912274, 
0.23137405, -0.02676277, 0.53285400, 0.12328859, 
0.22503029, -0.03667490, 0.54498664, 0.12263850, 
0.21830986, -0.02874519, 0.52107903, 0.11375669, 
0.21355203, -0.01883306, 0.43690349, 0.09330163, 
0.21077664, -0.00892092, 0.26318558, 0.05547337, 
0.20996978, -0.00079474, -0.04168983, -0.00875361, 
0.20822136, -0.01668949, -0.49720767, -0.10352926, 
0.20329398, -0.03258425, -0.43808922, -0.08906090, 
0.19518766, -0.04847900, -0.29022973, -0.05664926, 
0.18390238, -0.06437375, -0.17522726, -0.03222471, 
0.17039979, -0.06278428, -0.09609959, -0.01637535, 
0.15943241, -0.04688952, -0.04129409, -0.00658362, 
0.15164398, -0.03099477, 0.00203820, 0.00030908, 
0.14703450, -0.01510002, 0.04321886, 0.00635466, 
0.14560000, 0.00000000, 0.09134947, 0.01330048, 
0.14560000, 0.00000000, 0.15785155, 0.02298319, 
0.14560000, 0.00000000, 0.26193954, 0.03813840, 
0.14560000, 0.00000000, 0.45037391, 0.06557444, 
0.14560000, 0.00000000, 0.85548551, 0.12455869, 
0.14487200, -0.01617778, 1.85069281, 0.26811357, 
0.13804138, -0.05212840, 3.01590287, 0.41631940, 
0.12402064, -0.08807901, 1.74297497, 0.21616487, 
0.10280978, -0.12402963, 0.68836821, 0.07077098, 
0.07440879, -0.15998025, 0.24561207, 0.01827570, 
0.04530677, -0.12762469, 0.07149245, 0.00323909, 
0.02337689, -0.09167407, 0.01524455, 0.00035637, 
0.00863714, -0.05572346, 0.00305017, 0.00002634, 
0.00108751, -0.01977284, 0.00038207, 0.00000042}; 
