/* This file is part of Lemma, a geophysical modelling and inversion API */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
  @file
  @author   M. Andy Kass and Trevor P. Irons
  @date     02/16/2011
            15 Dec 2018
  @version  $Id: digitalfiltersintrans.cpp 87 2013-09-05 22:44:05Z tirons $
 **/
#include "FastSinTransformAnderson.h"

namespace Lemma {

    // ====================  FRIENDS       =======================

    std::ostream &operator<<(std::ostream &stream,
			const FastSinTransformAnderson &ob) {
		stream << *(DigitalFilterIntegratorAnderson<Real>*)(&ob);
		return stream;
	}

    // ====================  LIFECYCLE     =======================

	FastSinTransformAnderson::FastSinTransformAnderson( const ctor_key& key ) :
		DigitalFilterIntegratorAnderson<Real>(key) {
        SetFilterWeights();
        NumConv = 1;
        ilow = 425;
        ihi = 460;
        ABSCISSA = 0.7745022656977834;
        //IntKernel = CosTransIntegrationKernel::New();
	}

	FastSinTransformAnderson::~FastSinTransformAnderson() {

    }

	std::shared_ptr<FastSinTransformAnderson> FastSinTransformAnderson::NewSP() {
        return std::make_shared< FastSinTransformAnderson > ( ctor_key() );
	}

    // ====================  OPERATIONS    =======================

	void FastSinTransformAnderson::SetFilterWeights() {
		//Same number of coefficients as the cosine transform
		FilterWeights.resize(787);
		Key.resize(787);
		Work.resize(787, NumRel);
		this->FilterWeights <<
			 4.519086190454403E-29,-9.339715413211410E-29,
			 1.907086488243319E-28,-2.926740419085585E-28,
			 4.016341837702778E-28,-5.205269186311504E-28,
			 6.517833605193130E-28,-7.967548954470954E-28,
			 9.568276718198612E-28,-1.135805242625555E-27,
			 1.341437536522928E-27,-1.584604744296628E-27,
			 1.876875146781600E-27,-2.228200512918392E-27,
			 2.645681468388641E-27,-3.133421673989624E-27,
			 3.693471763710930E-27,-4.327595342414010E-27,
			 5.039000943393479E-27,-5.833332055385210E-27,
			 6.719340442247252E-27,-7.710109799166923E-27,
			 8.824593601800077E-27,-1.008809737899913E-26,
			 1.153087819007531E-26,-1.318573428833282E-26,
			 1.508632848921759E-26,-1.726724501006653E-26,
			 1.976529598469166E-26,-2.262087271971451E-26,
			 2.587877027540831E-26,-2.958891513809359E-26,
			 3.380756725224869E-26,-3.859914775323363E-26,
			 4.403862178004457E-26,-5.021419292439053E-26,
			 5.722969551574750E-26,-6.520606418485730E-26,
			 7.428212579422239E-26,-8.461557977402292E-26,
			 9.638471499797232E-26,-1.097907018143775E-25,
			 1.250600971971666E-25,-1.424476805594983E-25,
			 1.622403124908015E-25,-1.847622752118429E-25,
			 2.103817835334522E-25,-2.395181391816518E-25,
			 2.726499236157535E-25,-3.103251036607772E-25,
			 3.531729413199891E-25,-4.019163393605676E-25,
			 4.573837905690991E-25,-5.205218550552940E-25,
			 5.924100002797128E-25,-6.742788104825517E-25,
			 7.675312493515405E-25,-8.737657967045221E-25,
			 9.948010684981015E-25,-1.132702852601557E-24,
			 1.289815274051798E-24,-1.468796997184372E-24,
			 1.672663454907744E-24,-1.904836740815919E-24,
			 2.169205882613385E-24,-2.470198700421404E-24,
			 2.812864533285517E-24,-3.202964869374407E-24,
			 3.647071555907292E-24,-4.152674762505081E-24,
			 4.728305934616842E-24,-5.383678610889903E-24,
			 6.129850575416668E-24,-6.979408353295871E-24,
			 7.946678501710549E-24,-9.047967050654569E-24,
			 1.030183273201298E-23,-1.172939535974881E-23,
			 1.335468970408732E-23,-1.520506989792332E-23,
			 1.731167873568262E-23,-1.970998238900646E-23,
			 2.244038375223756E-23,-2.554891109141771E-23,
			 2.908800212317214E-23,-3.311738161673479E-23,
			 3.770506652613824E-23,-4.292849755751231E-23,
			 4.887584419793589E-23,-5.564747348119901E-23,
			 6.335764555403829E-23,-7.213641884192625E-23,
			 8.213185708614141E-23,-9.351250590466155E-23,
			 1.064702652070505E-22,-1.212235989202909E-22,
			 1.380212637669216E-22,-1.571464627021063E-22,
			 1.789216833692896E-22,-2.037140677202572E-22,
			 2.319416886961351E-22,-2.640804920121902E-22,
			 3.006724483628496E-22,-3.423345344607581E-22,
			 3.897693304501770E-22,-4.437766344557916E-22,
			 5.052672367873663E-22,-5.752779264041773E-22,
			 6.549893990733216E-22,-7.457456427231128E-22,
			 8.490772387335222E-22,-9.667263925372798E-22,
			 1.100677264803472E-21,-1.253188268156373E-21,
			 1.426831572556448E-21,-1.624534745260255E-21,
			 1.849632235986410E-21,-2.105919014055614E-21,
			 2.397717720265674E-21,-2.729947694949692E-21,
			 3.108212647296628E-21,-3.538889390172954E-21,
			 4.029242408342459E-21,-4.587537765144882E-21,
			 5.223192986426113E-21,-5.946923044249243E-21,
			 6.770936697567055E-21,-7.709123239579199E-21,
			 8.777310068392340E-21,-9.993501047681958E-21,
			 1.137821494603412E-20,-1.295478887104638E-20,
			 1.474982378032821E-20,-1.679356954738640E-20,
			 1.912051261376801E-20,-2.176986279743765E-20,
			 2.478633017643540E-20,-2.822073770460957E-20,
			 3.213105082813427E-20,-3.658314411923333E-20,
			 4.165216959294550E-20,-4.742350946454843E-20,
			 5.399460006022600E-20,-6.147610566668155E-20,
			 6.999435769179613E-20,-7.969278499925461E-20,
			 9.073518741196294E-20,-1.033074536152729E-19,
			 1.176219711201683E-19,-1.339196499267872E-19,
			 1.524758875590042E-19,-1.736028891015458E-19,
			 1.976577702338448E-19,-2.250451123066827E-19,
			 2.562280190911125E-19,-2.917307540064815E-19,
			 3.321538976139149E-19,-3.781767593800005E-19,
			 4.305782565276538E-19,-4.902385383010367E-19,
			 5.581678864101238E-19,-6.355065796403268E-19,
			 7.235650952324198E-19,-8.238205902566872E-19,
			 9.379730988161989E-19,-1.067935983426557E-18,
			 1.215914876207947E-18,-1.384387860555074E-18,
			 1.576216891832665E-18,-1.794611006906676E-18,
			 2.043284318190411E-18,-2.326391762796314E-18,
			 2.648754138285296E-18,-3.015750110424166E-18,
			 3.433638103530407E-18,-3.909379456027323E-18,
			 4.451100704654134E-18,-5.067809360821606E-18,
			 5.770060327858650E-18,-6.569505440663543E-18,
			 7.479857530176959E-18,-8.516184129746393E-18,
			 9.696306653881282E-18,-1.103970228659850E-17,
			 1.256954070708544E-17,-1.431098828414357E-17,
			 1.629418091510444E-17,-1.855161949305473E-17,
			 2.112251982431457E-17,-2.404883030225413E-17,
			 2.738161098629106E-17,-3.117496715967868E-17,
			 3.549542289668629E-17,-4.041270829342227E-17,
			 4.601355794199069E-17,-5.238775618130511E-17,
			 5.964848186475663E-17,-6.791121691023222E-17,
			 7.732378583243061E-17,-8.803453656899252E-17,
			 1.002367506589228E-16,-1.141207151607239E-16,
			 1.299394517387315E-16,-1.479366207688721E-16,
			 1.684438994882969E-16,-1.917726554733372E-16,
			 2.183583387005876E-16,-2.485978764937954E-16,
			 2.830639416126730E-16,-3.222610765667943E-16,
			 3.669438668141347E-16,-4.177514390747528E-16,
			 4.756802050039284E-16,-5.415364164475966E-16,
			 6.166389337226809E-16,-7.019997076546317E-16,
			 7.993689686576395E-16,-9.100089857117708E-16,
			 1.036249133688131E-15,-1.179651807131579E-15,
			 1.343326900422591E-15,-1.529189515686284E-15,
			 1.741405751368545E-15,-1.982293701749077E-15,
			 2.257454882110670E-15,-2.569648892095082E-15,
			 2.926436822402734E-15,-3.331029913939900E-15,
			 3.793676909909576E-15,-4.317994472774402E-15,
			 4.917935321484997E-15,-5.597373071100983E-15,
			 6.375390057182862E-15,-7.255792277807143E-15,
			 8.264801128606280E-15,-9.405537165055569E-15,
			 1.071420644035709E-14,-1.219214915931198E-14,
			 1.388960394313136E-14,-1.580427268552795E-14,
			 1.800620968515390E-14,-2.048641568507301E-14,
			 2.334305662501363E-14,-2.655548553367103E-14,
			 3.026192648607248E-14,-3.442221623150520E-14,
			 3.923190211789030E-14,-4.461893198803410E-14,
			 5.086121105139434E-14,-5.783551844666699E-14,
			 6.593852855730308E-14,-7.496602415439665E-14,
			 8.548655485671044E-14,-9.716902808177407E-14,
			 1.108315208765312E-13,-1.259458312388695E-13,
			 1.436933683252974E-13,-1.632417225266264E-13,
			 1.863027688321447E-13,-2.115771091886518E-13,
			 2.415529925720814E-13,-2.742172912312053E-13,
			 3.131970387082062E-13,-3.553922261911766E-13,
			 4.061035675187256E-13,-4.605809413353380E-13,
			 5.265892490959544E-13,-5.968795167949857E-13,
			 6.828504569587442E-13,-7.734770560272592E-13,
			 8.855241689907420E-13,-1.002271124202202E-12,
			 1.148416995714124E-12,-1.298663208549853E-12,
			 1.489453100122077E-12,-1.682586391404361E-12,
			 1.931907280346413E-12,-2.179832324535619E-12,
			 2.506009817027883E-12,-2.823763626714695E-12,
			 3.251036383068994E-12,-3.657522083511441E-12,
			 4.218031428263349E-12,-4.736873852220176E-12,
			 5.473359729916149E-12,-6.133871906007721E-12,
			 7.103341924139109E-12,-7.941565166210412E-12,
			 9.220310756445447E-12,-1.028004550802915E-11,
			 1.197053221213684E-11,-1.330420077896753E-11,
			 1.554457869729160E-11,-1.721363713771749E-11,
			 2.019093243336348E-11,-2.226535054417105E-11,
			 2.623385317715458E-11,-2.878986806971887E-11,
			 3.409688864363201E-11,-3.721174703331319E-11,
			 4.433387089687385E-11,-4.807551416154768E-11,
			 5.766987237954167E-11,-6.207834479976159E-11,
			 7.505545387359396E-11,-8.011101399321720E-11,
			 9.773871151888171E-11,-1.033088762718738E-10,
			 1.273612451487001E-10,-1.331148100865271E-10,
			 1.660864014336979E-10,-1.713561270888201E-10,
			 2.167712428480381E-10,-2.203372791851255E-10,
			 2.831980148718330E-10,-2.829496057001224E-10,
			 3.703869422887365E-10,-3.627980397893734E-10,
			 4.850207201792002E-10,-4.643421461158355E-10,
			 6.360231449851816E-10,-5.930443189593078E-10,
			 8.353515059977503E-10,-7.555102296535103E-10,
			 1.099086883072858E-09,-9.595938165682892E-10,
			 1.448941662513427E-09,-1.214418403431928E-09,
			 1.914354201982380E-09,-1.530232541828562E-09,
			 2.535413701041661E-09,-1.917967238636924E-09,
			 3.366964327985339E-09,-2.388280225383556E-09,
			 4.484391763894045E-09,-2.949747512489630E-09,
			 5.991820026480242E-09,-3.605669450820265E-09,
			 8.033774905885646E-09,-4.348662889559140E-09,
			 1.081185161881095E-08,-5.151760029833092E-09,
			 1.460863092797377E-08,-5.954048869440942E-09,
			 1.982212746243125E-08,-6.637850452739543E-09,
			 2.701558565884670E-08,-6.992855428994142E-09,
			 3.698969905307490E-08,-6.660268099150364E-09,
			 5.088766862234823E-08,-5.046427612646975E-09,
			 7.034845702641431E-08,-1.189990213788075E-09,
			 9.773091311662091E-08, 6.441339406826419E-09,
			 1.364422877792574E-07, 2.026069653953343E-08,
			 1.914207530941986E-07, 4.403297240671824E-08,
			 2.698454243003982E-07, 8.358850780049443E-08,
			 3.821828678435025E-07, 1.479022772000465E-07,
			 5.437318168094116E-07, 2.507226084953915E-07,
			 7.769062342581499E-07, 4.130252690891796E-07,
			 1.114613518638701E-06, 6.667060493527094E-07,
			 1.605258236346765E-06, 1.060130280292916E-06,
			 2.320160162069900E-06, 1.666464612725961E-06,
			 3.364560133136435E-06, 2.596174981355472E-06,
			 4.893960156014256E-06, 4.015759771727380E-06,
			 7.138397535039002E-06, 6.175810373704275E-06,
			 1.043852386492282E-05, 9.453018910283816E-06,
			 1.529925306344126E-05, 1.441303290654501E-05,
			 2.246956262435983E-05, 2.190445818635350E-05,
			 3.306123161466435E-05, 3.319938341030514E-05,
			 4.872554987486263E-05, 5.020335754327977E-05,
			 7.191633170111086E-05, 7.576900218644445E-05,
			 1.062813859178838E-04, 1.141641643802547E-04,
			 1.572450969332647E-04, 1.717703221930222E-04,
			 2.328751169425117E-04, 2.581236364185096E-04,
			 3.451709156798280E-04, 3.874650245753196E-04,
			 5.119775374980107E-04, 5.810445069347065E-04,
			 7.598232475621811E-04, 8.705390306182757E-04,
			 1.128116358716784E-03, 1.303104717626917E-03,
			 1.675327916301618E-03, 1.948807411825891E-03,
			 2.488044976374601E-03, 2.911467293668464E-03,
			 3.694103557020186E-03, 4.344298949393989E-03,
			 5.481360712089968E-03, 6.472046368434359E-03,
			 8.123895409393892E-03, 9.621355456586993E-03,
			 1.201713561934862E-02, 1.426025794636169E-02,
			 1.772160768805842E-02, 2.104435746141294E-02,
			 2.600944034318140E-02, 3.085828026010451E-02,
			 3.789358111566572E-02, 4.481923933568410E-02,
			 5.458716136402632E-02, 6.416184799000865E-02,
			 7.727199941242613E-02, 8.982755932806265E-02,
			 1.064254421326244E-01, 1.214134956891936E-01,
			 1.402491646624913E-01, 1.549103199447484E-01,
			 1.715485184963992E-01, 1.786033886777877E-01,
			 1.827088851861087E-01, 1.675422102829242E-01,
			 1.407983439987153E-01, 8.162579672849707E-02,
			 2.858447717701069E-03,-1.152686206415223E-01,
			-2.421516386308682E-01,-3.812981622302894E-01,
			-4.639824707365586E-01,-4.676754754771468E-01,
			-2.983922369012484E-01, 1.962768518309340E-02,
			 4.615749449787655E-01, 7.571539594142682E-01,
			 6.725778299920618E-01,-2.282965939549971E-02,
			-8.636206091858209E-01,-1.015125148503644E+00,
			 2.432665171231830E-01, 1.368855569487176E+00,
			 2.856162774022951E-01,-1.804149507828080E+00,
			 4.533604735331026E-01, 1.511758555237049E+00,
			-1.909629765056948E+00, 1.069005333649147E+00,
			-1.178375735699469E-01,-4.119085433366451E-01,
			 5.558053315672025E-01,-5.042611820681206E-01,
			 3.952161415642411E-01,-2.910574896760750E-01,
			 2.096946427258310E-01,-1.509580770735921E-01,
			 1.097522132187282E-01,-8.093658545655293E-02,
			 6.057900864438948E-02,-4.595801396907676E-02,
			 3.526341496281775E-02,-2.730346497971181E-02,
			 2.128837318669908E-02,-1.668596224808419E-02,
			 1.312967661769313E-02,-1.036095586387300E-02,
			 8.193157054943619E-03,-6.488727811475892E-03,
			 5.144495374133109E-03,-4.081960541714881E-03,
			 3.240723341083809E-03,-2.573908860969868E-03,
			 2.044902564517464E-03,-1.624966594846773E-03,
			 1.291465382262761E-03,-1.026523739285122E-03,
			 8.159991714412245E-04,-6.486871353788918E-04,
			 5.157019263358405E-04,-4.099917485806924E-04,
			 3.259573396167529E-04,-2.591511272468608E-04,
			 2.060393933618002E-04,-1.638139563220660E-04,
			 1.302428944388295E-04,-1.035521166699833E-04,
			 8.233134695725269E-05,-6.545945702523444E-05,
			 5.204514861201607E-05,-4.137981961749043E-05,
			 3.290010486595251E-05,-2.615810167862320E-05,
			 2.079770185899022E-05,-1.653577691984197E-05,
			 1.314722074735249E-05,-1.045305829437006E-05,
			 8.310991516938568E-06,-6.607882958945550E-06,
			 5.253779852702802E-06,-4.177162948246520E-06,
			 3.321169005036239E-06,-2.640587391141323E-06,
			 2.099472167888885E-06,-1.669243535881050E-06,
			 1.327178346968277E-06,-1.055209941709689E-06,
			 8.389739249503043E-07,-6.670494862601122E-07,
			 5.303561942591048E-07,-4.216744016303114E-07,
			 3.352639284891773E-07,-2.665608855859320E-07,
			 2.119366259147424E-07,-1.685060930903601E-07,
			 1.339754432660642E-07,-1.065208923693739E-07,
			 8.469239020916003E-08,-6.733703409093301E-08,
			 5.353817677449518E-08,-4.256701249734076E-08,
			 3.384408402893838E-08,-2.690867780042694E-08,
			 2.139449069787337E-08,-1.701028327972431E-08,
			 1.352449755955155E-08,-1.075302693551076E-08,
			 8.549492340901277E-09,-6.797511037206932E-09,
			 5.404549702807423E-09,-4.297037155315087E-09,
			 3.416478584420968E-09,-2.716366067339561E-09,
			 2.159722190085306E-09,-1.717147034705988E-09,
			 1.365265381135002E-09,-1.085492111933322E-09,
			 8.630506137215972E-10,-6.861923302473438E-10,
			 5.455762461365737E-10,-4.337755280138903E-10,
			 3.448852659061754E-10,-2.742105973115728E-10,
			 2.180187416052945E-10,-1.733418480408352E-10,
			 1.378202445493526E-10,-1.095778083781342E-10,
			 8.712287608917021E-11,-6.926945929969819E-11,
			 5.507460505331545E-11,-4.378859244194077E-11,
			 3.481533505726639E-11,-2.768089786642390E-11,
			 2.200846567772674E-11,-1.749844112121302E-11,
			 1.391262099629252E-11,-1.106161524020212E-11,
			 8.794844030523375E-12,-6.992584703096528E-12,
			 5.559648432809331E-12,-4.420352703548207E-12,
			 3.514524031458616E-12,-2.794319819206459E-12,
			 2.221701482790797E-12,-1.766425390825141E-12,
			 1.404445505192163E-12,-1.116643356280387E-12,
			 8.878182745412279E-13,-7.058845460186685E-13,
			 5.612330885763100E-13,-4.462239349060042E-13,
			 3.547827170807447E-13,-2.820798403939499E-13,
			 2.242754016089481E-13,-1.783163791396228E-13,
			 1.417753834852610E-13,-1.127224512924624E-13,
			 8.962311166429105E-14,-7.125734094978236E-14,
			 5.665512550244704E-14,-4.504522906558543E-14,
			 3.581445886076434E-14,-2.847527896066489E-14,
			 2.264006040254001E-14,-1.800060802704875E-14,
			 1.431188272386055E-14,-1.137905935138482E-14,
			 9.047236776658255E-15,-7.193256557121187E-15,
			 5.719198156731723E-15,-4.547207137145127E-15,
			 3.615383167608584E-15,-2.874510673128837E-15,
			 2.285459445620894E-15,-1.817117927723045E-15,
			 1.444750012769246E-15,-1.148688573014634E-15,
			 9.132967130053839E-16,-7.261418852616671E-16,
			 5.773392480475140E-16,-4.590295837506217E-16,
			 3.649642034053721E-16,-2.901749135190327E-16,
			 2.307116140436942E-16,-1.834336683660563E-16,
			 1.458440262302222E-16,-1.159573385656211E-16,
			 9.219509852266826E-17,-7.330227044488768E-17,
			 5.828100342071381E-17,-4.633792840399525E-17,
			 3.684225532762789E-17,-2.929245705146663E-17,
			 2.328978051105255E-17,-1.851718602164869E-17,
			 1.472260238767692E-17,-1.170561341297906E-17,
			 9.306872641520070E-18,-7.399687253379369E-18,
			 5.883326607803712E-18,-4.677702014739752E-18,
			 3.719136739613880E-18,-2.957002828302571E-18,
			 2.351047121536452E-18,-1.869265228476306E-18,
			 1.486211170428986E-18,-1.181653416196487E-18,
			 9.395063257031646E-19,-7.469805646126344E-19,
			 5.939076179015729E-19,-4.722027256379258E-19,
			 3.754378751739167E-19,-2.985022967459849E-19,
			 2.373325310854237E-19,-1.886978121843854E-19,
			 1.500294299097576E-19,-1.192850600158091E-19,
			 9.484089595818352E-20,-7.540588530116191E-20,
			 5.995354099387067E-20,-4.766772603294524E-20,
			 3.789954805412417E-20,-3.013308718206562E-20,
			 2.395814700817093E-20,-1.904858950112549E-20,
			 1.514510957672512E-20,-1.204153954009819E-20,
			 9.573960050057665E-21,-7.612042487983742E-21,
			 6.052165469011701E-21,-4.811941935554926E-21,
			 3.825867772694447E-21,-3.041862118819870E-21,
			 2.418516642409082E-21,-1.922908502426471E-21,
			 1.528861481986123E-21,-1.215563454903229E-21,
			 9.664671642003589E-22,-7.684162553978440E-22,
			 6.109504047471497E-22,-4.857528416823409E-22,
			 3.862110855330143E-22,-3.070676966569801E-22,
			 2.441425971113178E-22,-1.941122955877971E-22,
			 1.543343556015419E-22,-1.227078345565842E-22,
			 9.756232141971099E-23,-7.756971208813704E-23,
			 6.167406266892664E-23,-4.903581613923544E-23,
			 3.898745781389350E-23,-3.099825880130062E-23,
			 2.464624570708451E-23,-1.959591536406367E-23,
			 1.558051651712082E-23,-1.238796173479821E-23,
			 9.849625195167609E-24,-7.831435654861331E-24,
			 6.226795451209084E-24,-4.950951685405124E-24,
			 3.936520905478440E-24,-3.129929802298849E-24,
			 2.488584770157100E-24,-1.978622297628744E-24,
			 1.573121213803113E-24,-1.250680505229501E-24,
			 9.942866354722078E-25,-7.904119407074957E-25,
			 6.282983380266727E-25,-4.993888550242444E-25,
			 3.968764501205991E-25,-3.153465565806142E-25,
			 2.504952335417932E-25,-1.989067071293495E-25,
			 1.578744037087885E-25,-1.252528942885154E-25,
			 9.933547263601893E-26,-7.875756004541075E-26,
			 6.242484682723995E-26,-4.946074258240189E-26,
			 3.916606766138584E-26,-3.098609190290296E-26,
			 2.448266612392087E-26,-1.931034281011451E-26,
			 1.519618180226741E-26,-1.192353131496834E-26,
			 9.319757733847061E-27,-7.247010142017766E-27,
			 5.595281281317008E-27,-4.277815801389812E-27,
			 3.228199604942252E-27,-2.397244120563833E-27,
			 1.748239591243191E-27,-1.251355005015151E-27,
			 8.794257877849950E-28,-6.065291790558063E-28,
			 4.090426687827314E-28,-2.676669295980934E-28,
			 1.687971022918484E-28,-1.044337763175647E-28,
			 7.050578391076381E-29,-6.406578964496667E-29,
			 8.047966445795522E-29,-1.121534977637725E-28,
			 1.496948518403447E-28,-1.846610467538164E-28,
			 2.120865254113486E-28,-2.314246444782675E-28,
			 2.456355516626332E-28,-2.590895710468579E-28,
			 2.753571339247125E-28,-2.961734255384709E-28,
			 3.222852751815456E-28,-3.554096868418778E-28,
			 3.994470369697907E-28,-4.595315984451220E-28,
			 5.391210400875100E-28,-6.364075603215328E-28,
			 7.416537866632483E-28,-8.373375968928217E-28,
			 9.020712825598172E-28,-9.167392508097227E-28,
			 8.694251225012477E-28,-7.570921079500922E-28,
			 5.849601896353324E-28,-3.650523966203355E-28,
			 1.141119602484722E-28, 1.491703156191346E-28,
			-4.067578199248336E-28, 6.427512747502163E-28,
			-8.440676076304842E-28, 1.001129119104450E-27,
			-1.108757116989416E-27, 1.166928305547677E-27,
			-1.180901419514423E-27, 1.160312647193067E-27,
			-1.116872557002111E-27, 1.060982755116985E-27,
			-9.988396142394386E-28, 9.317938546853034E-28,
			-8.581732798065989E-28, 7.758565868660186E-28,
			-6.839003286369139E-28, 5.828348637958973E-28,
			-4.740105434766476E-28, 3.587009166849001E-28,
			-2.377198496417097E-28, 1.119160774411077E-28,
			 1.670017331897950E-29,-1.438060858130858E-28,
			 2.622750906188666E-28,-3.630328238235802E-28,
			 4.369496766662814E-28,-4.761183982698324E-28,
			-3.708525899969828E-28;
	}
} // end namespace Lemma

