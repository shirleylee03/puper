//
// Created on 2020/10/10.
//
#include "product.h"

index_t CHashtable::hashfunction(CPN_Product *node) {
    index_t hashvalue;
    index_t size = CHASHSIZE-1;
    hashvalue = node->RGname_ptr->Hash();
    hashvalue = hashvalue & size;

    index_t Prohashvalue = hashvalue + node->BAname_id;
    Prohashvalue = Prohashvalue & size;
    return Prohashvalue;
}
// hast table
CPN_Product *CHashtable::search(CPN_Product *node) {
    index_t idx = hashfunction(node);
    CPN_Product *p = table[idx];
    while(p!=NULL)
    {
        if(p->BAname_id==node->BAname_id && p->RGname_ptr==node->RGname_ptr)
            return p;
        p=p->hashnext;
    }
    return NULL;
}

void CHashtable::remove(CPN_Product *node) {
    index_t idx = hashfunction(node);
    CPN_Product *p=table[idx];
    CPN_Product *q;
    if(p->BAname_id==node->BAname_id && p->RGname_ptr==node->RGname_ptr)
    {
        q=p->hashnext;
        table[idx] = q;
        delete p;
        return;
    }

    q=p;
    p=p->hashnext;
    while(p!=NULL)
    {
        if(p->BAname_id==node->BAname_id && p->RGname_ptr==node->RGname_ptr)
        {
            q->hashnext=p->hashnext;
            delete p;
            return;
        }

        q=p;
        p=p->hashnext;
    }
    cerr<<"Couldn't delete from hashtable!"<<endl;
}

void CHashtable::resetHash() {
    for(int i=0;i<CHASHSIZE;++i)
    {
        if(table[i]!=NULL) {
            CPN_Product *p=table[i];
            CPN_Product *q;
            while(p!=NULL) {
                q=p->hashnext;
                delete p;
                p=q;
            }
        }
    }
    memset(table,NULL,sizeof(CPN_Product *)*CHASHSIZE);
    nodecount = 0;
    hash_conflict_times = 0;
}

void CHashtable::insert(CPN_Product *node) {
    index_t idx = hashfunction(node);
    if(table[idx]!=NULL)
        hash_conflict_times++;
    node->hashnext = table[idx];
    table[idx] = node;
    nodecount++;
}

CPstack::CPstack() {
    toppoint = 0;
    hashlink = new index_t[CHASHSIZE];
    memset(hashlink,UNREACHABLE,sizeof(index_t)*CHASHSIZE);
    mydata = new CPN_Product* [CHASHSIZE];
    memset(mydata,NULL,sizeof(CPN_Product*)*CHASHSIZE);
}

CPstack::~CPstack() {
    delete [] hashlink;
    for(int i=0;i<toppoint;++i)
    {
        if(mydata[i]!=NULL)
            delete mydata[i];
    }
    delete [] mydata;
}

index_t CPstack::hashfunction(CPN_Product *node) {
    index_t hashvalue = node->RGname_ptr->Hash();
    index_t size = CHASHSIZE-1;
    hashvalue = hashvalue & size;
    index_t  Prohashvalue = (hashvalue+node->BAname_id)&size;
    return Prohashvalue;
}

CPN_Product *CPstack::top() {
    return mydata[toppoint-1];
}

CPN_Product *CPstack::pop() {
    CPN_Product *popitem = mydata[--toppoint];
    index_t hashpos = hashfunction(popitem);
    hashlink[hashpos] = popitem->stacknext;
    mydata[toppoint] = NULL;
    return popitem;
}

CPN_Product *CPstack::search(CPN_Product *node) {
    index_t hashpos = hashfunction(node);
    index_t pos = hashlink[hashpos];
    CPN_Product *p;
    while(pos!=UNREACHABLE)
    {
        p=mydata[pos];
        if(p->BAname_id==node->BAname_id && p->RGname_ptr==node->RGname_ptr)
        {
            return p;
        }
        pos = p->stacknext;
    }
    return NULL;
}

int CPstack::push(CPN_Product *node) {
    if(toppoint >= CHASHSIZE) {
        return ERROR;
    }
    index_t hashpos = hashfunction(node);
    node->stacknext = hashlink[hashpos];
    hashlink[hashpos] = toppoint;
    mydata[toppoint++] = node;
    return OK;
}

NUM_t CPstack::size() {
    return toppoint;
}

bool CPstack::empty() {
    return (toppoint==0)?true:false;
}

void CPstack::clear() {
    toppoint = 0;
    for(int i=0;i<toppoint;++i)
    {
        if(mydata[i]!=NULL) {
            delete mydata[i];
        }
    }
    memset(mydata,NULL, sizeof(CPN_Product*)*CHASHSIZE);
    memset(hashlink,UNREACHABLE,sizeof(index_t)*CHASHSIZE);
}

CPN_Product_Automata::CPN_Product_Automata(CPN *net,StateBuchi *sba, RG *rg) {
    cpn = net;
    this->ba = sba;
    this->rg = rg;
    result = true;
}

void CPN_Product_Automata::GetInitNode() {
//??????buchi???????????????????????????????????????????????????
    for(int i=0; i<ba->vex_num; i++)
    {
        if(ba->vertics[i].id == -1)
            continue;
        if(ba->vertics[i].initial)
        {
            //???????????????????????????????????????????????????????????????????????????????????????
            if(isLabel(rg->init_node, i))
            {
                //??????????????????????????????
                CPN_Product N;
                N.BAname_id = i;
                N.RGname_ptr = rg->init_node;
                //???????????????????????????
                initial_status.push_back(N);
            }
        }
    }
}

/*bool Product_Automata::isLabel(RGNode *state, int sj)
 * function: ?????????????????????????????????buchi?????????????????????????????????????????????
 * in: state,?????????????????????????????????????????????????????????
 * sj,buchi???????????????????????????????????????
 * out: true(?????????????????????) or false(??????????????????)
 * */
bool CPN_Product_Automata::isLabel(RG_NODE *state, int sj) {

    //???????????????????????????label
    string str = ba->vertics[sj].label;
    if(str == "true")
        return true;

    bool mark = false;
    while (1)
    {
        int pos = str.find_first_of("&&");

        if (pos == string::npos)     //????????????????????????
        {
            //cout<<str;
            switch (judgeF(str)) {
                case LTLC: {
                    mark = handleLTLC(str, state);
                    if(mark == false)
                        return false;
                    break;
                }
                case LTLF: {
                    /*a && b && c:
                    * true: ??????true
                    * false??? ??????????????????false
                    * */
                    mark = handleLTLF(str, state);
                    if(mark == false)
                        return false;
                    break;
                }
                case LTLV: {
                    mark = handleLTLV(str,state);
                    if(mark == false)
                        return false;
                    break;
                }
            }
            break;
        }

        string subprop = str.substr(0, pos);    //????????????????????????
        //cout<<subprop<<" ";

        switch (judgeF(subprop))   //???????????????F????????????
        {
            case LTLC: {
                /*a && b && c:
                * true: ??????true
                * false??? ??????????????????false
                * */
                mark = handleLTLC(subprop, state);
                if (mark == false)
                    return false; //??????????????????????????????
                break;
            }
            case LTLF: {
                /*a && b && c:
                * true: ??????true
                * false??? ??????????????????false
                * */
                mark = handleLTLF(subprop, state);
                if (mark == false) {
                    //???????????????????????????
                    return false;
                }
                break;
            }
            case LTLV: {
                mark = handleLTLV(subprop,state);
                if(mark == false)
                    return false;
                break;
            }
        }
        //cout<<endl;
        str = str.substr(pos + 2, str.length() - pos -2);
    }
    return true;
}

/*function:???????????????Fireability??????
 * */
int CPN_Product_Automata::judgeF(string s) {
    int pos = s.find("token-count");
    if (pos != string::npos)
        return LTLC;
    pos = s.find("token-value");
    if (pos != string::npos)
        return LTLV;
    return LTLF;
}

/*bool Product_Automata::handleLTLF(string s, RGNode *state)
 * function:??????F???????????????????????????????????????state???????????????
 * in: s???????????????????????????????????????????????? state?????????
 * out: true(??????) or false(?????????)
 * */
bool CPN_Product_Automata::handleLTLF(string s, RG_NODE *state) {
    if(s[0] == '!') //????????????'!'???is-fireable{}
    {
        /*!{t1 || t2 || t3}???
         * true???t1???????????? ?????? t2???????????? ?????? t3????????????
         * false??? ????????????????????????
         * */
        s = s.substr(2,s.length()-2); //?????????!{???
        while(1)
        {
            int pos = s.find_first_of(",");
            if (pos < 0)
                break;
            string subs = s.substr(0, pos);            //??????????????????

            if(state->fireable(subs))
                return false;

            s = s.substr(pos + 1, s.length() - pos);
        }
        return true;

    } else{         //?????????is-fireable{}????????????
        /*{t1 || t2 || t3}:
	     * true: ????????????????????????
	     * false: ???????????????
	     * */
        s = s.substr(1, s.length() - 1);//?????????{???

        while(1)
        {
            int pos = s.find_first_of(",");
            if (pos < 0)
                break;
            string subs = s.substr(0, pos);  //??????????????????

            if(state->fireable(subs))
                return true;

            //????????????????????????????????????????????????
            s = s.substr(pos + 1, s.length() - pos);
        }
        //????????????????????????????????????????????????
        return false;
    }
}

/*bool Product_Automata::handleLTLC(string s, RGNode *state)
 * function: ??????C????????????????????????????????????s?????????state???????????????
 * in: s,??????????????? state,??????
 * out: true(??????) or false(?????????)
 * */
bool CPN_Product_Automata::handleLTLC(string s, RG_NODE *state) {
    short int front_sum, latter_sum;     //??????????????? ???????????????
    if(s[0] == '!')
    {
        /*!(front <= latter)
	     * true:front > latter
	     * false:front <= latter
	     * */
        s = s.substr(2, s.length() - 2);   //??????"!{"
        handleLTLCstep(front_sum, latter_sum, s, state);
        if(front_sum <= latter_sum)
            return false;
        else
            return true;
    }
    else {
        /*(front <= latter)
         * true:front <= latter
         * false:front > latter
         * */
        s = s.substr(1, s.length() - 1);   //??????"{"
        handleLTLCstep(front_sum, latter_sum, s, state);
        if(front_sum <= latter_sum)
            return true;
        else
            return false;
    }
}

/*void handleLTLCstep(int &front_sum, int &latter_sum, string s, RGNode *state)
 * function:???????????????state??????C??????"<="???????????????token???front_sum??????????????????token???latter_sum
 * in: s,????????? state,??????
 * out: front_sum??????????????????, latter_sum??????????????????
 * */
void CPN_Product_Automata::handleLTLCstep(short int &front_sum, short int &latter_sum, string s, RG_NODE *state) {
    if(s[0] == 't')   //???????????????token-count?????????
    {
        int pos = s.find_first_of("<=");           //?????????<=???
        string s_token = s.substr(12, pos - 13);   //??????"token-count(" ")"  ????????p1,p2,
        front_sum = sumtoken(s_token, state);      //??????token???

        //????????????????????????
        s = s.substr(pos + 2, s.length() - pos - 2); //????????????????????????????????? ????????????+}

        if(s[0] == 't')   //???????????????token-count
        {
            string s_token = s.substr(12, s.length() - 14);
            latter_sum = sumtoken(s_token, state);
        }
        else{             //?????????????????????
            s = s.substr(0, s.length() - 1);        //???????????????}
            latter_sum = atoi(s.c_str());
        }
    }
    else{             //????????????????????????????????????????????????token-count
        //??????????????????  ???????????? ?????????????????????
        int pos = s.find_first_of("<=");//?????????<=,??????????????????
        string num = s.substr(0, pos);//????????????
        front_sum = atoi(num.c_str());
        //	 cout<< " "<<front_sum<<" ";

        //??????????????????
        s = s.substr(pos + 14, s.length() - pos - 16);
        //	 cout<<" "<<s<<" ";
        latter_sum = sumtoken(s, state);
    }
}

/*int Product_Automata::sumtoken(string s, RGNode *state)
 * function: ???????????????state?????????????????????token???
 * in: s:p1,p2,p3,p4,?????????????????????????????????state?????????
 * out: ?????????token???
 * */
short int CPN_Product_Automata::sumtoken(string s, RG_NODE *state) {
    short int sum = 0;
    while(1)
    {
        int pos = s.find_first_of(",");
        if (pos == string::npos)
            break;
        string subs = s.substr(0, pos);        //????????????p1

        map<string,index_t>::iterator piter;
        piter = cpn->mapPlace.find(subs);
        sum += state->marking.mss[piter->second].tokennum();

        //?????????????????????P1?????? ???p2??????????????????s???
        s = s.substr(pos + 1, s.length() - pos);
    }
    return sum;
}

void CPN_Product_Automata::GetProduct() {
    //??????????????????rg???????????????????????????????????????????????????
    if(rg->init_node == NULL){
        rg->init(cpn);
    }

    //?????????????????????????????????
    GetInitNode();

    //???????????????????????????
    vector<CPN_Product>::iterator it_P;
    for(it_P = initial_status.begin(); it_P != initial_status.end(); it_P++)
    {
        CPN_Product *init = new CPN_Product;
        init->RGname_ptr = (*it_P).RGname_ptr;
        init->BAname_id = (*it_P).BAname_id;
//        dfs1(init);
        Tarjan(init);
    }
}

int sum=0;
void CPN_Product_Automata::Tarjan(CPN_Product *pnode) {
    elapse_end=clock();
    if((elapse_end-elapse_begin)/1000000.0>MaxTime) {
        timeup= true;
        return;
    }
    if(!result)
        return;
    pnode->lowlink = pnode->id = cstack.toppoint;
    cstack.push(pnode);
    if(ba->vertics[pnode->BAname_id].accepted)
        astack.push(pnode);
    ArcNode *pba = ba->vertics[pnode->BAname_id].firstarc;

    /**/
    if(!pnode->RGname_ptr->tranQ_obtained) {cerr<<"fireset hasn't been calculated"<<endl;}
    FireTranQ *tranQ;

    while(pba) {
        if(!result)
            return;
        if(pnode->RGname_ptr->firenum == 0) {
            /*RG doesn't have a successor node*/
            RG_NODE *rgseed = pnode->RGname_ptr;
            if(isLabel(rgseed,pba->destination)) {
                CPN_Product *qs = new CPN_Product;
                qs->RGname_ptr = rgseed;
                qs->BAname_id = pba->destination;

                CPN_Product *existpos = cstack.search(qs);
                if(existpos!=NULL) {
                    /*this node exists in statck*/
                    pnode->lowlink = (pnode->lowlink < existpos->lowlink)?pnode->lowlink:existpos->lowlink;
                    if(!astack.empty()) {
                        CPN_Product *cur_accp = astack.top();
                        if(cur_accp->id >= existpos->id) {
                            result = false;
                            return;
                        }
                    }
                }
                else if(h.search(qs)==NULL) {
                    Tarjan(qs);
                    pnode->lowlink = (pnode->lowlink<qs->lowlink)?pnode->lowlink:qs->lowlink;
                }
            }
        }
        else {
            for(tranQ=pnode->RGname_ptr->tranQ->next;tranQ;tranQ=tranQ->next)
            {
                for(unsigned int k=0;k<tranQ->bindings.size();k++) {
                    if(!result)
                        return;
                    RG_NODE *newnode = new RG_NODE;
                    newnode->marking.init_marking(pnode->RGname_ptr->marking);

                    Marking_after_fire(newnode->marking, tranQ->transition, tranQ->bindings[k], cpn);

                    RG_NODE *rgseed = rg->nodeExist(newnode);

                    if (rgseed == NULL) {
//                        cout << sum++ <<endl;
                        rgseed = newnode;
                        newnode->fathernum = pnode->RGname_ptr->num;
                        newnode->last_tran = tranQ->transition->getid();
                        rgseed->get_FireTranQ(cpn);
                        rg->addRGNode(newnode);

                    } else {
                        delete newnode;
                    }

                    if (rgseed->tranQ_obtained == false) {
                        cerr << "fireset hasn't been calculated" << endl;
                    }
                    if (isLabel(rgseed, pba->destination)) {
                        CPN_Product *qs = new CPN_Product;
                        qs->RGname_ptr = rgseed;
                        qs->BAname_id = pba->destination;
                        CPN_Product *existpos = cstack.search(qs);
                        if (existpos != NULL) {
                            pnode->lowlink = (pnode->lowlink < existpos->lowlink) ? pnode->lowlink : existpos->lowlink;
                            if (!astack.empty()) {
                                CPN_Product *cur_accp = astack.top();
                                if (cur_accp->id >= existpos->id) {
                                    result = false;
                                    return;
                                }
                            }
                        } else if (h.search(qs) == NULL) {
                            Tarjan(qs);
                            pnode->lowlink = (pnode->lowlink < qs->lowlink) ? pnode->lowlink : qs->lowlink;
                        }
                    }
                }
            }
        }
        pba=pba->next;
    }
    CPN_Product *popitem;
    if(pnode->lowlink == pnode->id) {
        do {
            popitem = cstack.pop();
            if(!astack.empty() && popitem == astack.top())
                astack.pop();
            h.insert(popitem);
        }while (pnode!=popitem);
    }
}

void CPN_Product_Automata::printresult(string propertyid) {

    string ret=(this->result)?"TRUE":"FALSE";
//    cout<<propertyid<<" "<<ret<<endl;
    cout<<"checked result:"<<ret<<endl;
}

bool CPN_Product_Automata::handleLTLV(string s, RG_NODE *state) {
    int pos = s.find("==");
    if(pos!=string::npos) {
        //equality
        if(s[0] == '!')
        {
            /*!(front == latter)
             * true:front != latter
             * false:front == latter
             * */
            s = s.substr(2, s.length() - 3);   //??????"!{}"
            int p = s.find_first_of("==");
            string front = s.substr(0,p);
            string latter = s.substr(p+2);
            bucket front_color,latter_color;
            if(!FetchColor(front,state,front_color))
                return false;
            if(!FetchColor(latter,state,latter_color))
                return false;
            if(front_color == latter_color)
                return false;
            else
                return true;
        }
        else {
            /*(front == latter)
             * true:front == latter
             * false:front != latter
             * */
            s = s.substr(1, s.length() - 2);   //??????"{}"
            int p = s.find_first_of("==");
            string front = s.substr(0,p);
            string latter = s.substr(p+2);
            bucket front_color,latter_color;
            if(!FetchColor(front,state,front_color))
                return false;
            if(!FetchColor(latter,state,latter_color))
                return false;
            if(front_color == latter_color)
                return true;
            else
                return false;
        }
    }

    pos = s.find("<=");
    if(pos!=string::npos) {
        if(s[0]=='!') {
            /*!(front <= latter)
             * true:front !<= latter
             * false:front <= latter
             * */
            s = s.substr(2, s.length() - 3);   //??????"!{}"
            int p = s.find_first_of("<=");
            string front = s.substr(0,p);
            string latter = s.substr(p+2);
            bucket front_color,latter_color;
            if(!FetchColor(front,state,front_color))
                return false;
            if(!FetchColor(latter,state,latter_color))
                return false;
            if(front_color <= latter_color)
                return false;
            else
                return true;
        }
        else {
            /*(front <= latter)
             * true:front <= latter
             * false:front !<= latter
             * */
            s = s.substr(1, s.length() - 2);   //??????"{}"
            int p = s.find_first_of("<=");
            string front = s.substr(0,p);
            string latter = s.substr(p+2);
            bucket front_color,latter_color;
            if(!FetchColor(front,state,front_color))
                return false;
            if(!FetchColor(latter,state,latter_color))
                return false;
            if(front_color <= latter_color)
                return true;
            else
                return false;
        }
    }

    if(s[0]=='!') {
        /*!(front < latter)
         * true:front !< latter
         * false:front < latter
         * */
        s = s.substr(2, s.length() - 3);   //??????"!{}"
        int p = s.find_first_of("<");
        string front = s.substr(0,p);
        string latter = s.substr(p+1);
        bucket front_color,latter_color;
        if(!FetchColor(front,state,front_color))
            return false;
        if(!FetchColor(latter,state,latter_color))
            return false;
        if(front_color < latter_color)
            return false;
        else
            return true;
    }
    else {
        /*(front < latter)
         * true:front < latter
         * false:front !< latter
         * */
        s = s.substr(1, s.length() - 2);   //??????"{}"
        int p = s.find_first_of("<");
        string front = s.substr(0,p);
        string latter = s.substr(p+1);
        bucket front_color,latter_color;
        if(!FetchColor(front,state,front_color))
            return false;
        if(!FetchColor(latter,state,latter_color))
            return false;
        if(front_color < latter_color)
            return true;
        else
            return false;
    }
}

//FetchColor???????????????????????????????????????????????????????????????????????????(????????????)????????????
bool CPN_Product_Automata::FetchColor(string s, RG_NODE *state, bucket &color) {
    if(s[0]=='t') {
        string value = s.substr(12, s.length() - 13);
        auto valueVec = split(value,"#");
        if(valueVec.size() != 3)
            throw "token-value??????????????????????????????????????????????????????!";
        string P_name = valueVec[0], index = valueVec[1], thread = valueVec[2];
        auto iter = cpn->mapPlace.find(P_name);
        if(iter == cpn->mapPlace.end())
            throw "???????????????" + P_name + " in product.cpp!";
        CPlace &pp = cpn->getplacearr()[iter->second];
        auto tks = state->marking.mss[iter->second].getmapTokens();
        auto tkiter = tks.begin();
        while(tkiter != tks.end()){
            auto tmp_tk = tkiter->first;
            SORTID sid = tmp_tk->getsid();
            auto ps = sorttable.find_productsort(sid);
            if(index == "NULL" ^ ps.get_hasindex() && thread == "NULL" ^ ps.get_hastid()){
                if(index == "NULL" && thread == "NULL"){
                    //??????????????????
                    if(tks.size() != 1)
                        throw "FetchColor????????????????????????????????????token?????????1";
                    Bucket tmp_bkt, value_bkt;
                    tmp_tk->getcolor(tmp_bkt);
                    tmp_bkt.getVarValue(value_bkt);
                    color.generateFromBucket(value_bkt);
                    return true;
                }
                else if(index != "NULL" && thread == "NULL"){
                    //??????????????????
                    Bucket tmp_bkt, value_bkt, index_bkt;
                    tmp_tk->getcolor(tmp_bkt);
                    tmp_bkt.pro[tmp_bkt.pro.size()-2]->getcolor(index_bkt);
                    if(index_bkt == atoi(index.c_str())) {
                        tmp_bkt.getVarValue(value_bkt);
                        color.generateFromBucket(value_bkt);
                        return true;
                    }
                }
                else if(index == "NULL" && thread != "NULL"){
                    //??????????????????
                    Bucket tmp_bkt, value_bkt, tid_bkt;
                    tmp_tk->getcolor(tmp_bkt);
                    tmp_bkt.pro[tmp_bkt.pro.size()-1]->getcolor(tid_bkt);
                    if(tid_bkt == thread) {
                        tmp_bkt.getVarValue(value_bkt);
                        color.generateFromBucket(value_bkt);
                        return true;
                    }
                }
                else if(index != "NULL" && thread != "NULL"){
                    //??????????????????
                    Bucket tmp_bkt, value_bkt, index_bkt, tid_bkt;
                    tmp_tk->getcolor(tmp_bkt);
                    tmp_bkt.pro[tmp_bkt.pro.size()-3]->getcolor(index_bkt);
                    tmp_bkt.pro[tmp_bkt.pro.size()-1]->getcolor(tid_bkt);
                    if(index_bkt == atoi(index.c_str()) && tid_bkt == thread) {
                        tmp_bkt.getVarValue(value_bkt);
                        color.generateFromBucket(value_bkt);
                        return true;
                    }
                }
            }
            else
                throw "??????" + P_name + "???index???tid????????????????????????!";
            tkiter++;
        }
        return false;
    }
    else if(s[0] == 'i') {
        string num = s.substr(13,s.length()-14);
        color.icolor = atoi(num.c_str());
    }
    else if(s[0] == 'r') {
        string num = s.substr(14,s.length()-15);
        color.rcolor = atof(num.c_str());
    }
    else if(s[0] == 's') {
        color.scolor=s.substr(16,s.length()-17);
    }
    return true;
}
