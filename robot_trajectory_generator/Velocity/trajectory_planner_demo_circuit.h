double len=404; 
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
0.20997591, 0.00043081, 0.00000000, 0.00000000, 
0.21092370, 0.00904708, 0.00000000, 0.00000000, 
0.21359474, 0.01766334, 0.00000000, 0.00000000, 
0.21798903, 0.02627960, 0.00000000, 0.00000000, 
0.22410658, 0.03489586, 0.00000000, 0.00000000, 
0.23084449, 0.02972610, 0.00000000, 0.00000000, 
0.23592809, 0.02110984, 0.00000000, 0.00000000, 
0.23928843, 0.01249358, 0.00000000, 0.00000000, 
0.24092552, 0.00387732, 0.00000000, 0.00000000, 
0.24110000, -0.00000000, 0.00000000, 0.00000000, 
0.24110000, -0.00000000, 0.00000000, 0.00000000, 
0.24110000, -0.00000000, 0.00000000, 0.00000000, 
0.24110000, -0.00000000, 0.00000000, 0.00000000, 
0.24108900, -0.00044001, 0.00000000, 0.00000000, 
0.24082499, -0.00220007, 0.00000000, 0.00000000, 
0.24020897, -0.00396013, 0.00000000, 0.00000000, 
0.23924094, -0.00572019, 0.00000000, 0.00000000, 
0.23792089, -0.00748025, 0.00000000, 0.00000000, 
0.23660085, -0.00572019, 0.00000000, 0.00000000, 
0.23563281, -0.00396013, 0.00000000, 0.00000000, 
0.23501679, -0.00220007, 0.00000000, 0.00000000, 
0.23475278, -0.00044001, 0.00000000, 0.00000000, 
0.23414554, -0.00851775, 0.24832401, 0.05814396, 
0.23122517, -0.02068595, 0.46395857, 0.10727890, 
0.22587116, -0.03285416, 0.53880548, 0.12170062, 
0.21808351, -0.04502237, 0.52824076, 0.11520060, 
0.20983346, -0.03528780, 0.48543945, 0.10186144, 
0.20399272, -0.02311959, 0.44310277, 0.09038974, 
0.20058562, -0.01095139, 0.41070006, 0.08238053, 
0.19960000, -0.00000000, 0.39077081, 0.07799785, 
0.19960000, 0.00000000, 0.38107637, 0.07606284, 
0.19960000, 0.00000000, 0.38004914, 0.07585781, 
0.19960000, 0.00000000, 0.38772784, 0.07739048, 
0.19962245, 0.00089800, 0.40381185, 0.08060991, 
0.20016125, 0.00449002, 0.42820260, 0.08570957, 
0.20141846, 0.00808204, 0.45848466, 0.09234728, 
0.20339407, 0.01167406, 0.48758408, 0.09917171, 
0.20594261, 0.01203327, 0.49985656, 0.10294177, 
0.20799006, 0.00844125, 0.46564317, 0.09684915, 
0.20931911, 0.00484923, 0.34939921, 0.07313593, 
0.20992975, 0.00125721, 0.12343098, 0.02591183, 
0.20994666, -0.00045161, 0.17682543, 0.03712391, 
0.20978107, -0.00120430, 0.38172739, 0.08007918, 
0.20946494, -0.00195698, 0.48231682, 0.10102846, 
0.20899827, -0.00270966, 0.50870441, 0.10631834, 
0.20847742, -0.00225805, 0.49470708, 0.10313525, 
0.20810107, -0.00150537, 0.46586929, 0.09694790, 
0.20787527, -0.00075268, 0.43656644, 0.09075136, 
0.20780000, -0.00000000, 0.41357775, 0.08594146, 
0.20780000, -0.00000000, 0.39946650, 0.08300914, 
0.20780000, -0.00000000, 0.39500715, 0.08208249, 
0.20780000, -0.00000000, 0.40039459, 0.08320200, 
0.20780169, 0.00011290, 0.41539108, 0.08631897, 
0.20789954, 0.00086559, 0.43915346, 0.09129980, 
0.20814793, 0.00161827, 0.46881392, 0.09758265, 
0.20854685, 0.00237096, 0.49703906, 0.10365593, 
0.20907787, 0.00259676, 0.50849929, 0.10631595, 
0.20952195, 0.00184408, 0.47654959, 0.09984760, 
0.20981550, 0.00109139, 0.36710313, 0.07702393, 
0.20995851, 0.00033871, 0.15138083, 0.03178369, 
0.20651584, -0.06915833, 0.00000000, 0.00000000, 
0.17885250, -0.20747499, 0.00000000, 0.00000000, 
0.12691460, -0.24896999, 0.00000000, 0.00000000, 
0.09095227, -0.11065333, 0.00000000, 0.00000000, 
0.08210000, -0.00000000, -0.00000000, -0.00000000, 
0.08210000, -0.00000000, -0.00000000, -0.00000000, 
0.08218584, 0.00572270, -0.00000000, -0.00000000, 
0.08714551, 0.04387401, -0.00000000, -0.00000000, 
0.09973545, 0.08202533, -0.00000000, -0.00000000, 
0.11232538, 0.04387401, -0.00000000, -0.00000000, 
0.11728505, 0.00572270, -0.00000000, -0.00000000, 
0.11710292, -0.00334961, 0.00000000, 0.00000000, 
0.11601430, -0.00753662, 0.00000000, 0.00000000, 
0.11444208, -0.00628052, 0.00000000, 0.00000000, 
0.11360468, -0.00209351, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11358479, 0.00188416, -0.00000000, -0.00000000, 
0.11438032, 0.00607117, -0.00000000, -0.00000000, 
0.11593789, 0.00774597, -0.00000000, -0.00000000, 
0.11706838, 0.00355896, -0.00000000, -0.00000000, 
0.11736671, -0.00041870, 0.00000000, 0.00000000, 
0.11686426, -0.00460571, 0.00000000, 0.00000000, 
0.11552442, -0.00879272, 0.00000000, 0.00000000, 
0.11410293, -0.00502441, 0.00000000, 0.00000000, 
0.11351675, -0.00083740, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11373552, 0.00314026, -0.00000000, -0.00000000, 
0.11478227, 0.00732727, -0.00000000, -0.00000000, 
0.11636496, 0.00648987, -0.00000000, -0.00000000, 
0.11724423, 0.00230286, -0.00000000, -0.00000000, 
0.11730390, -0.00167480, 0.00000000, 0.00000000, 
0.11655024, -0.00586182, 0.00000000, 0.00000000, 
0.11501151, -0.00795532, 0.00000000, 0.00000000, 
0.11383915, -0.00376831, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350105, 0.00020935, -0.00000000, -0.00000000, 
0.11396162, 0.00439636, -0.00000000, -0.00000000, 
0.11525959, 0.00858337, -0.00000000, -0.00000000, 
0.11671667, 0.00523376, -0.00000000, -0.00000000, 
0.11734472, 0.00104675, -0.00000000, -0.00000000, 
0.11716573, -0.00293091, 0.00000000, 0.00000000, 
0.11616085, -0.00711792, 0.00000000, 0.00000000, 
0.11457187, -0.00669922, 0.00000000, 0.00000000, 
0.11365073, -0.00251221, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11355129, 0.00146545, -0.00000000, -0.00000000, 
0.11426308, 0.00565247, -0.00000000, -0.00000000, 
0.11577878, 0.00816467, -0.00000000, -0.00000000, 
0.11699301, 0.00397766, -0.00000000, -0.00000000, 
0.11737089, 0.00000000, 0.00000000, 0.00000000, 
0.11695219, -0.00418701, 0.00000000, 0.00000000, 
0.11569609, -0.00837402, 0.00000000, 0.00000000, 
0.11420760, -0.00544311, 0.00000000, 0.00000000, 
0.11353768, -0.00125610, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11367690, 0.00272156, -0.00000000, -0.00000000, 
0.11463991, 0.00690857, -0.00000000, -0.00000000, 
0.11623098, 0.00690857, -0.00000000, -0.00000000, 
0.11719399, 0.00272156, -0.00000000, -0.00000000, 
0.11733321, -0.00125610, 0.00000000, 0.00000000, 
0.11666329, -0.00544311, 0.00000000, 0.00000000, 
0.11517480, -0.00837402, 0.00000000, 0.00000000, 
0.11391870, -0.00418701, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11387788, 0.00397766, -0.00000000, -0.00000000, 
0.11509211, 0.00816467, -0.00000000, -0.00000000, 
0.11660781, 0.00565247, -0.00000000, -0.00000000, 
0.11731960, 0.00146545, -0.00000000, -0.00000000, 
0.11722016, -0.00251221, 0.00000000, 0.00000000, 
0.11629902, -0.00669922, 0.00000000, 0.00000000, 
0.11471005, -0.00711792, 0.00000000, 0.00000000, 
0.11370516, -0.00293091, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11352617, 0.00104675, -0.00000000, -0.00000000, 
0.11415422, 0.00523376, -0.00000000, -0.00000000, 
0.11561130, 0.00858337, -0.00000000, -0.00000000, 
0.11690927, 0.00439636, -0.00000000, -0.00000000, 
0.11736985, 0.00020935, -0.00000000, -0.00000000, 
0.11703174, -0.00376831, 0.00000000, 0.00000000, 
0.11585938, -0.00795532, 0.00000000, 0.00000000, 
0.11432065, -0.00586182, 0.00000000, 0.00000000, 
0.11356699, -0.00167480, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11362666, 0.00230286, -0.00000000, -0.00000000, 
0.11450593, 0.00648987, -0.00000000, -0.00000000, 
0.11608862, 0.00732727, -0.00000000, -0.00000000, 
0.11713537, 0.00314026, -0.00000000, -0.00000000, 
0.11735414, -0.00083740, 0.00000000, 0.00000000, 
0.11676796, -0.00502441, 0.00000000, 0.00000000, 
0.11534647, -0.00879272, 0.00000000, 0.00000000, 
0.11400663, -0.00460571, 0.00000000, 0.00000000, 
0.11350419, -0.00041870, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11380251, 0.00355896, -0.00000000, -0.00000000, 
0.11493300, 0.00774597, -0.00000000, -0.00000000, 
0.11649057, 0.00607117, -0.00000000, -0.00000000, 
0.11728611, 0.00188416, -0.00000000, -0.00000000, 
0.11726622, -0.00209351, 0.00000000, 0.00000000, 
0.11642881, -0.00628052, 0.00000000, 0.00000000, 
0.11485659, -0.00753662, 0.00000000, 0.00000000, 
0.11376797, -0.00334961, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11350942, 0.00062805, -0.00000000, -0.00000000, 
0.11405373, 0.00481506, -0.00000000, -0.00000000, 
0.11543545, 0.00900207, -0.00000000, -0.00000000, 
0.11681716, 0.00481506, -0.00000000, -0.00000000, 
0.11736147, 0.00062805, -0.00000000, -0.00000000, 
0.11710292, -0.00334961, 0.00000000, 0.00000000, 
0.11601430, -0.00753662, 0.00000000, 0.00000000, 
0.11444208, -0.00628052, 0.00000000, 0.00000000, 
0.11360468, -0.00209351, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11358479, 0.00188416, -0.00000000, -0.00000000, 
0.11438032, 0.00607117, -0.00000000, -0.00000000, 
0.11593789, 0.00774597, -0.00000000, -0.00000000, 
0.11706838, 0.00355896, -0.00000000, -0.00000000, 
0.11736671, -0.00041870, 0.00000000, 0.00000000, 
0.11686426, -0.00460571, 0.00000000, 0.00000000, 
0.11552442, -0.00879272, 0.00000000, 0.00000000, 
0.11410293, -0.00502441, 0.00000000, 0.00000000, 
0.11351675, -0.00083740, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, 0.00000000, 0.00000000, 
0.11350000, 0.00000000, -0.00000000, -0.00000000, 
0.11373552, 0.00314026, -0.00000000, -0.00000000, 
0.11478227, 0.00732727, -0.00000000, -0.00000000, 
0.11636496, 0.00648987, -0.00000000, -0.00000000, 
0.11724423, 0.00230286, -0.00000000, -0.00000000, 
0.11758959, 0.00546747, 0.05886195, 0.00692155, 
0.12004995, 0.01913614, 0.19639027, 0.02357664, 
0.12524405, 0.03280482, 0.32588981, 0.04081576, 
0.13317188, 0.04647349, 0.44705156, 0.05953470, 
0.14383344, 0.06014216, 0.54945350, 0.07902979, 
0.15722874, 0.07381084, 0.61618041, 0.09688127, 
0.17335778, 0.08747951, 0.63505621, 0.11009193, 
0.19222055, 0.10114818, 0.60931518, 0.11712290, 
0.21134986, 0.08884638, 0.54967535, 0.11617381, 
0.22775226, 0.07517770, 0.47454768, 0.10807931, 
0.24142094, 0.06150903, 0.40346568, 0.09740506, 
0.25235588, 0.04784036, 0.34427073, 0.08687874, 
0.26055708, 0.03417168, 0.29812670, 0.07767902, 
0.26602455, 0.02050301, 0.26362774, 0.07013145, 
0.26875828, 0.00683434, 0.23882641, 0.06418658, 
0.26910000, -0.00000000, 0.22226570, 0.05981170, 
0.26910000, 0.00000000, 0.21419146, 0.05763892, 
0.26910000, 0.00000000, 0.21409127, 0.05761196, 
0.26910000, 0.00000000, 0.22224692, 0.05980665, 
0.26910000, 0.00000000, 0.24019652, 0.06463688, 
0.26910000, 0.00000000, 0.27130409, 0.07300793, 
0.26910000, 0.00000000, 0.32209061, 0.08667458, 
0.26907576, -0.00242422, 0.40514611, 0.10901500, 
0.26616670, -0.02666637, 0.53915324, 0.14350464, 
0.25840921, -0.05090852, 0.75449990, 0.19496972, 
0.24580329, -0.07515067, 1.08291842, 0.26618491, 
0.22834894, -0.09939282, 1.44501801, 0.32996834, 
0.20604616, -0.12363497, 1.48528323, 0.30603691, 
0.17889496, -0.14787712, 1.08233208, 0.19362375, 
0.14689532, -0.17211927, 0.62751651, 0.09217924, 
0.11209571, -0.16484663, 0.31982662, 0.03585119, 
0.08155060, -0.14060448, 0.15120534, 0.01233089, 
0.05585392, -0.11636233, 0.06488338, 0.00362399, 
0.03500567, -0.09212017, 0.02446318, 0.00085635, 
0.01900585, -0.06787802, 0.00808843, 0.00015373, 
0.00785446, -0.04363587, 0.00229395, 0.00001802, 
0.00155150, -0.01939372, 0.00024384, 0.00000038}; 
