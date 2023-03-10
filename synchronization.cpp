//
// Created by leo on 2021/11/3.
//

#include "synchronization.h"


extern char LTLFfile[], LTLVfile[], LTLCfile[];

extern string controlflowArcExp(string arcexp);

extern string tid_str;

int SYNCH::judgeF(string s) {
    int pos = s.find("token-count");
    if (pos != string::npos)
        return LTLC;
    pos = s.find("token-value");
    if (pos != string::npos)
        return LTLV;
    return LTLF;
}

//void SYNCH::GetLTL(ofstream &out,TiXmlElement *p)
//{
//    string value = p->Value();
//    if (value == "all-paths")
//    {
//        GetLTL(out,p->FirstChildElement());
//    }
//    else if (value == "globally")
//    {
//        out << "G(";
//        GetLTL(out,p->FirstChildElement());
//        out << ")";
//    }
//    else if (value == "finally")
//    {
//        out << "F(";
//        GetLTL(out,p->FirstChildElement());
//        out << ")";
//    }
//    else if (value == "next")
//    {
//        out << "X(";
//        GetLTL(out,p->FirstChildElement());
//        out << ")";
//    }
//    else if (value == "negation")
//    {
//        out << "!(";
//        GetLTL(out,p->FirstChildElement());
//        out << ")";
//    }
//    else if(value == "conjunction" || value == "disjunction")
//    {
//        TiXmlElement *m, *n;
//        m = p->FirstChildElement();
//        GetLTL(out,m);
//        m = m->NextSiblingElement();
//        while(m) {
//            if(value == "conjunction")
//                out << "&&";
//            else
//                out << "||";
//            GetLTL(out,m);
//
//            m = m->NextSiblingElement();
//        }
//    }
//    else if (value == "until")
//    {
//        TiXmlElement *m, *n;
//        m = p->FirstChildElement();
//        n = m->NextSiblingElement();
//        string mValue = m->Value();
//        string nValue = n->Value();
//        if (mValue != "before")
//        {
//            cerr << "Error in XML file! The element until\'s first child is not before!" << endl;
//            exit(-1);
//        }
//        if (nValue != "reach")
//        {
//            cerr << "Error in XML file! The element until\'s second child is not reach!" << endl;
//            exit(-1);
//        }
//        out << "(";
//        GetLTL(out,m->FirstChildElement());
//        out << ")U(";
//        GetLTL(out,n->FirstChildElement());
//        out << ")";
//    }
//    else if (value == "less" || value == "equality" || value == "lesseq")
//    {
//        TiXmlElement *m, *n;
//        m = p->FirstChildElement();
//        n = m->NextSiblingElement();
//        string mValue = m->Value();
//        string nValue = n->Value();
//        out << "{";
//        if (mValue == "token-value")
//        {
//            out << "token-value(";
//            TiXmlElement *left = m->FirstChildElement();
//            while (left != NULL)
//            {
//                out << left->GetText() ;
//                string temp = left->GetText();
//                auto idx=cpn_synch->mapPlace.find(temp)->second;
//                P.push_back(idx);
//                if (temp == "")
//                    break;
//                left = left->NextSiblingElement();
//            }
//            out << ")";
//        }
//        else if (mValue == "int-constant"
//                 || mValue == "real-constant"
//                 || mValue == "string-constant")
//        {
//            out << m->GetText();
//        }
//        else {
//            cerr << "Error in XML file about the element integer-le!" << endl;
//            exit(-1);
//        }
//        if(value == "lesseq")
//            out << "<=";
//        else if(value == "less")
//            out << "<";
//        if(value == "equality")
//            out << "==";
//        if (nValue == "token-value")
//        {
//            out << "token-value(";
//            TiXmlElement *right = n->FirstChildElement();
//            while (right != NULL)
//            {
//                out << right->GetText() ;
//                string temp = right->GetText();
//                auto idx=cpn_synch->mapPlace.find(temp)->second;
//                P.push_back(idx);
//                right = right->NextSiblingElement();
//            }
//            out << ")";
//        }
//        else if (nValue == "int-constant"
//                 || nValue == "real-constant"
//                 || nValue == "string-constant")
//        {
//            out << n->GetText();
//        }
//        else {
//            cerr << "Error in XML file about the element integer-le!" << endl;
//            exit(-1);
//        }
//        out << "}";
//    }
//    else if (value == "is-fireable")
//    {
//        TiXmlElement *m;
//        m = p->FirstChildElement();
//        out << "is-fireable{";
//        while (m != NULL)
//        {
//            string Value = m->Value();
//
//            if (Value == "transition")
//            {
//                string temp = m->GetText();
//                auto idx=cpn_synch->mapTransition.find(temp)->second;
//                T.push_back(idx);
//                out << m->GetText() << ",";
//            }
//            else
//            {
//                cerr << "Error in XML file! One of the element is-firability\'s child is not transition!" << endl;
//                exit(-1);
//            }
//            m = m->NextSiblingElement();
//        }
//        out << "}";
//    }
//}

//void SYNCH::extract_targetPT(int number=1) {
//    TiXmlDocument *doc;
//    string file;
//    if (LTLtype == LTLC)
//        file = LTLCfile;
//    else if (LTLtype == LTLF)
//        file = LTLFfile;
//    else if (LTLtype == LTLV)
//        file = LTLVfile;
//    doc = new TiXmlDocument(file.c_str());
//    if (!doc->LoadFile()) {
//        cerr << doc->ErrorDesc() << endl;
//    }
//    file = "result.txt";
//    ofstream out(file.c_str(), ios::out | ios::app);
//
//    TiXmlElement *root = doc->RootElement();
//    if (root == NULL) {
//        cerr << "Failed to load file: no root element!" << endl;
//        doc->Clear();
//    }
//
//    TiXmlElement *p = root->FirstChildElement();
//    for (int i = 1; i < number; ++i) {
//        p = p->NextSiblingElement();
//    }
//
//    TiXmlElement *id = p->FirstChildElement("id");
//
//    TiXmlElement *formula = p->FirstChildElement("formula");
//
//
//    GetLTL(out,formula->FirstChildElement());
//
//    out.close();
//}

set<index_t> SYNCH::get_observesLTLF(string s) {
    set<index_t> observes;
    if (s[0] == '!') //????????????'!'???is-fireable{}
    {
        /*!{t1 || t2 || t3}???
         * true???t1???????????? ?????? t2???????????? ?????? t3????????????
         * false??? ????????????????????????
         * */
        s = s.substr(2, s.length() - 2); //?????????!{???
        while (1) {
            int pos = s.find_first_of(",");
            if (pos < 0)
                break;
            string subs = s.substr(0, pos);            //??????????????????

            auto titer = cpn_synch->mapTransition.find(subs);
            if (titer == cpn_synch->mapTransition.end())
                throw "can't find T:" + subs;
            observes.insert(titer->second);

            s = s.substr(pos + 1, s.length() - pos);
        }
        return observes;

    } else {         //?????????is-fireable{}????????????
        /*{t1 || t2 || t3}:
	     * true: ????????????????????????
	     * false: ???????????????
	     * */
        s = s.substr(1, s.length() - 1);//?????????{???

        while (1) {
            int pos = s.find_first_of(",");
            if (pos < 0)
                break;
            string subs = s.substr(0, pos);            //??????????????????

            auto titer = cpn_synch->mapTransition.find(subs);
            if (titer == cpn_synch->mapTransition.end())
                throw "can't find T:" + subs;
            observes.insert(titer->second);

            s = s.substr(pos + 1, s.length() - pos);
        }
        //????????????????????????????????????????????????
        return observes;
    }
}

void find_p(string s, CPN *cpn_synch, set<int> &observes) {
    while (1) {
        int pos = s.find_first_of(",");
        if (pos == string::npos)
            break;
        string subs = s.substr(0, pos);        //????????????p1

        map<string, index_t>::iterator piter;
        piter = cpn_synch->mapPlace.find(subs);
        observes.insert(piter->second);

        //?????????????????????P1?????? ???p2??????????????????s???
        s = s.substr(pos + 1, s.length() - pos);
    }

}

set<index_t> FetchPlace(string s, CPN *cpn) {
    set<index_t> observes;
    if (s[0] == 't')   //???????????????token-value?????????
    {
        string value = s.substr(12, s.length() - 13);   //??????"token-count(" ")"  ????????p1,p2,
        auto valueVec = split(value, "#");
        string P_name = valueVec[0];
        auto iter = cpn->mapPlace.find(P_name);
        if (iter == cpn->mapPlace.end())
            throw "???????????????" + P_name + " in synchronization.cpp!";
        observes.emplace(iter->second);
    }
    return observes;
}

set<index_t> SYNCH::get_observesLTLV(string s) {
    set<index_t> observes;
    if (s[0] == '!') {
        /*!(front <= latter)
	     * true:front > latter
	     * false:front <= latter
	     * */
        s = s.substr(2, s.length() - 3);   //??????"!{"
    } else {
        s = s.substr(1, s.length() - 2);   //??????"{"
    }

    string front, latter;
    int offset = 2;
    int pos = s.find_first_of("==");
    if (pos != string::npos) {
        front = s.substr(0, pos);
        latter = s.substr(pos + 2);
    }
    pos = s.find_first_of("<=");
    if (pos != string::npos) {
        front = s.substr(0, pos);
        latter = s.substr(pos + 2);
    }
    pos = s.find_first_of("<");
    if (pos != string::npos) {
        front = s.substr(0, pos);
        latter = s.substr(pos + 1);
        offset = 1;
    }
    //????????????
    auto tmp_obs = FetchPlace(front, cpn_synch);
    observes.insert(tmp_obs.begin(), tmp_obs.end());
    //????????????
    tmp_obs = FetchPlace(latter, cpn_synch);
    observes.insert(tmp_obs.begin(), tmp_obs.end());
    return observes;
}

void SYNCH::add_copy_obs(index_t BA_t, set<index_t> obs_T) {
    for (auto i = obs_T.begin(); i != obs_T.end(); i++) {
        auto t = cpn_synch->findT_byindex(*i);
        //??????copy??????????????????????????????????????????????????????
        string name = "CP" + to_string(*i);
        auto guard = t->get_guard().getexp();
        cpn_synch->Add_Transition(name, guard, "", NoneRow);
        //???
        auto t_pro = t->get_producer();
        for (auto j = t_pro.begin(); j != t_pro.end(); j++) {
            auto source = cpn_synch->findP_byindex(j->idx)->getid();
            auto target = name;
            auto arcExpression = j->arc_exp.getexp();
            auto arcType = j->arcType;
            auto sourceP = true;
            cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
        }

        auto t_con = t->get_consumer();
        for (auto j = t_con.begin(); j != t_con.end(); j++) {
            auto source = name;
            auto target = cpn_synch->findP_byindex(j->idx)->getid();
            auto arcExpression = j->arc_exp.getexp();
            auto arcType = j->arcType;
            auto sourceP = false;
            cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
        }

        //?????????????????????????????????????????????????????????
        CP_tran.emplace(cpn_synch->get_transcount() - 1);
        //??????T?????????CP???????????????????????????????????????
        map_T2CP.emplace(make_pair(*i, cpn_synch->get_transcount() - 1));

        ba_t_count++;
    }
}

void SYNCH::Add_selfloop(int idx) {
    auto p = cpn_synch->findP_byindex(idx);
    //??????
    string name;
    name = "Tf" + to_string(idx);
    auto guard = "";
    cpn_synch->Add_Transition(name, guard, "", NoneRow);
    //???
    bool sourceP;
    string isControlArc = "true";
    Arc_Type arcType = control;
    string arcExpression = controlflowArcExp(tid_str);
    string source = p->getid();
    string target = name;
    sourceP = true;
    cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
    source = name;
    target = p->getid();
    sourceP = false;
    cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
}

void SYNCH::clear_producer_consumer(CPN *cpn_synch) {
    auto place = cpn_synch->getplacearr();
    for (auto i = 0; i < cpn_synch->get_placecount(); i++) {
        place[i].get_producer().clear();
        place[i].get_consumer().clear();
    }
    auto transition = cpn_synch->gettransarr();
    for (auto i = 0; i < cpn_synch->get_transcount(); i++) {
        transition[i].get_producer().clear();
        transition[i].get_consumer().clear();
    }
}

void SYNCH::ba2cpn(LTLCategory type, int num, CPN *cpn) {
    string propertyid;
    Syntax_Tree syntaxTree;
    if (type == LTLC)
        syntaxTree.ParseXML(LTLCfile, propertyid, num);
    else if (type == LTLF)
        syntaxTree.ParseXML(LTLFfile, propertyid, num);
    else if (type == LTLV)
        syntaxTree.ParseXML(LTLVfile, propertyid, num);
//    cout<<"formula tree:"<<endl;
//    syntaxTree.PrintTree();
//    cout<<"-----------------------------------"<<endl;
    syntaxTree.Push_Negation(syntaxTree.root);
//        cout<<"after negation:"<<endl;
//        syntaxTree.PrintTree();
//        cout<<"-----------------------------------"<<endl;
    syntaxTree.SimplifyLTL();
//        cout<<"after simplification:"<<endl;
//        syntaxTree.PrintTree();
//        cout<<"-----------------------------------"<<endl;
    syntaxTree.Universe(syntaxTree.root);
//        cout<<"after universe"<<endl;
//        syntaxTree.PrintTree();
//        cout<<"-----------------------------------"<<endl;

    syntaxTree.Get_DNF(syntaxTree.root);
    syntaxTree.Build_VWAA();
    syntaxTree.VWAA_Simplify();

    General GBA;
    GBA.Build_GBA(syntaxTree);
    GBA.Simplify();
    GBA.self_check();

    Buchi BA;
    BA.Build_BA(GBA);
    BA.Simplify();
    BA.self_check();
    BA.Backward_chaining();
    //BA.PrintBuchi("BA");

    //a place for each state q of the automaton
    //with only the initial state q0 having a token
    //The type of all its places is{???}
    cpn_synch = cpn;
    //??????????????????
    if (cpn_synch->map_t2conflictT.empty())
        cpn_synch->unf_init();

    q_begin_idx = cpn_synch->get_placecount();
    ba_t_begin_idx = cpn_synch->get_transcount();
//    cpn_synch->BA_tBeginIdx=ba_t_begin_idx;
    auto vertics = BA.get_vertics();
    q_count = 0;
    for (int i = 0; i < BA.get_vex_num(); i++) {
        if (vertics[i].id == -1)
            continue;
        auto name = 'Q' + to_string(q_count);
        auto colorset = "String";
        cpn_synch->Add_Place(name, colorset, true, SizeList(), "", false, false, NoneRow);
        //initial state is always stored in vertics[0]
        if (i == 0) {
            condition_tree ct;
            MultiSet ms;
            auto msi = sorttable.find_typename(colorset);
            ct.construct("1`'ba_init'");//??????token
            cpn_synch->CT2MS(ct, ms, msi.tid, msi.sid);
            auto pp = cpn_synch->findP_byid(name);
            pp->AddMultiSet(ms);
        }
        map_state2place.insert(make_pair(vertics[i].id, cpn_synch->get_placecount() - 1));
        map_place2state.insert(make_pair(cpn_synch->get_placecount() - 1, vertics[i].id));
        if (vertics[i].accepted)
            state_accepted.insert(cpn_synch->get_placecount() - 1);
        q_count++;
    }
    //For each transition (q, x, q???)of A????
    // the M-net has a transition (q, x, q???),
    // where q and q???are the
    // input and output places of the transition,
    // and x is its guard.
    ba_t_count = 0;
    u_count = 0;
    for (int i = 0; i < BA.get_vex_num(); i++) {
        if (vertics[i].id == -1)
            continue;
        for (BA_delta *p1 = vertics[i].firstarc; p1; p1 = p1->next) {
            string name;
            if (state_accepted.count(map_state2place.find(p1->destination)->second)) {
                name = 'I' + to_string(I_idx.size());
                I_idx.insert(cpn->get_transcount());
            } else name = 'u' + to_string(u_count++);
            auto guard = "";
            cpn_synch->Add_Transition(name, guard, "", NoneRow);
            //???
            bool sourceP;
            string isControlArc = "true";
            Arc_Type arcType = control;
            string arcExpression = controlflowArcExp(tid_str);
            string source = 'Q' + to_string(i);
            string target = name;
            sourceP = true;
            cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
            source = name;
            target = cpn_synch->findP_byindex(map_state2place.find(p1->destination)->second)->getid();
            sourceP = false;
            cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
            map_t2predicates.insert(make_pair(cpn_synch->get_transcount() - 1, p1->predicates));
            ba_t_count++;
        }
    }
}

void SYNCH::synch() {
    //For each place p which appears in the guard x
    // add arcs from p to (q, x, q???) and back
    //?????????????????????????????????????????????guard
    //???????????????????????????T?????????T???????????????????????????????????????????????????????????????T???guard?????????????????????????????????guard(??????
    //BA_T???guard???T???????????????
    //???????????????????????????T???????????????
    for (auto i = map_t2predicates.begin(); i != map_t2predicates.end(); i++) {
        if (i->second.empty())
            continue;
        set<int> observes_P;
        set<int> observes_T;
        set<string> guard;//?????????????????????????????????predicates
        //???observes
        for (auto j = i->second.begin(); j != i->second.end(); j++) {
            switch (judgeF(*j)) {
                case LTLF: {
                    auto obs_T = get_observesLTLF(*j);
                    if (!obs_T.empty()) {
                        observes_T.insert(obs_T.begin(), obs_T.end());
                        guard.insert(*j);
                        add_copy_obs(i->first, obs_T);
                    }
                    break;
                }
                case LTLV: {
                    auto obs_P = get_observesLTLV(*j);
                    if (!obs_P.empty()) {
                        guard.insert(*j);
                        observes_P.insert(obs_P.begin(), obs_P.end());
                    }
                    break;
                }
            }
        }

        for (auto j = observes_T.begin(); j != observes_T.end(); j++) {
            auto T_producer = cpn_synch->findT_byindex(*j)->get_producer();
            for (auto ipro = T_producer.begin(); ipro != T_producer.end(); ipro++) {
                observes_P.insert(ipro->idx);
            }
        }
        visible_P = observes_P;
        //??????t???guard
        if (!guard.empty())
            map_t2guard.insert(make_pair(i->first, guard));
        //??????
        //?????????????????????????????????BA??????????????????BA?????????????????????guard?????????????????????????????????????????????

        for (auto iobs = observes_P.begin(); iobs != observes_P.end(); iobs++) {
            auto p_pro = cpn_synch->findP_byindex(*iobs)->get_producer();
            for (auto ipro = p_pro.begin(); ipro != p_pro.end(); ipro++) {
                visible_T.insert(ipro->idx);
            }
            auto p_con = cpn_synch->findP_byindex(*iobs)->get_consumer();
            for (auto icon = p_con.begin(); icon != p_con.end(); icon++) {
                visible_T.insert(icon->idx);
            }
        }
    }
//Add scheduler places B and S
    //B is connected by arcs going from B to every B??uchi transition (u0,u1 and I0),
    // and going from every visible transition (t1 and t2)to B
    //B contains ??? and S is empty
    auto name = "B";
    auto colorset = "String";
    cpn_synch->Add_Place(name, colorset, true, SizeList(), "", false, false, NoneRow);
    //???token
    condition_tree ct;
    MultiSet ms;
    auto msi = sorttable.find_typename(colorset);
    ct.construct("1`'ba_init'");//??????token
    cpn_synch->CT2MS(ct, ms, msi.tid, msi.sid);
    auto pp = cpn_synch->findP_byid(name);
    pp->AddMultiSet(ms);
    //??????
    for (auto i = ba_t_begin_idx; i < cpn_synch->get_transcount(); i++) {
        bool sourceP;
        string isControlArc = "true";
        Arc_Type arcType = control;
        string arcExpression = controlflowArcExp(tid_str);
        string source = "B";
        string target = cpn_synch->findT_byindex(i)->getid();
        sourceP = true;
        cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
    }
    //??????
    for (auto i = visible_T.begin(); i != visible_T.end(); i++) {
        bool sourceP;
        string isControlArc = "true";
        Arc_Type arcType = control;
        string arcExpression = controlflowArcExp(tid_str);
        string source = cpn_synch->findT_byindex(*i)->getid();
        string target = "B";
        sourceP = false;
        cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
    }

    //S is connected by arcs going from S to every visible transition (t1 and t2),
    // and going from every B??uchi transition (u0,u1 and I0) to S
    name = "S";
    colorset = "String";
    cpn_synch->Add_Place(name, colorset, true, SizeList(), "", false, false, NoneRow);
    //??????
    for (auto i = visible_T.begin(); i != visible_T.end(); i++) {
        bool sourceP;
        string isControlArc = "true";
        Arc_Type arcType = control;
        string arcExpression = controlflowArcExp(tid_str);
        string source = "S";
        string target = cpn_synch->findT_byindex(*i)->getid();
        sourceP = true;
        cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
    }
    //??????
    for (auto i = ba_t_begin_idx; i < cpn_synch->get_transcount(); i++) {
        bool sourceP;
        string isControlArc = "true";
        Arc_Type arcType = control;
        string arcExpression = controlflowArcExp(tid_str);
        string source = cpn_synch->findT_byindex(i)->getid();
        string target = "S";
        sourceP = false;
        cpn_synch->Add_Arc(source, target, arcExpression, sourceP, arcType, normal);
    }

//    //????????????+
//    for (auto i = 0; i < q_begin_idx; i++) {
//        auto p = cpn_synch->findP_byindex(i);
////        if (p->getExp() == "abort begin")
//        if (p->getExp() == "abort_v")
//            Add_selfloop(i);
//        if (!p->get_producer().empty() && p->get_consumer().empty())
//            Add_selfloop(i);
//    }
//    //????????????-
    clear_producer_consumer(cpn_synch);
    cpn_synch->set_producer_consumer();

//    cpn_synch->print_CPN("cpn_ba");
}