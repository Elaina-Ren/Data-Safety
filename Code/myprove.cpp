#include<libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>
#include<fstream>
#include"common.hpp"
using namespace libsnark;
using namespace std;
int main(){
    int x;
    cin>>x;
    int secret[6];
    secret[0] = x;
    secret[1] = x;
    secret[2] = x*x;
    secret[3] = x*x*x;
    secret[4] = x*x*x+x;
    secret[5] = x*x*x+x+5;
    //输入隐私数据构造面包板
    protoboard<FieldT>pb=build_protoboard(secret);
    const r1cs_constraint_system<FieldT>constraint_system=pb.get_constraint_system();
    cout<<"Public Output: "<<pb.primary_input()<<endl;
    cout<<"Private Output: "<<pb.auxiliary_input()<<endl;
    //加载证明密钥
    fstream f_pk("pk.raw", ios_base::in);
    r1cs_gg_ppzksnark_proving_key<libff::default_ec_pp>pk;
    f_pk>>pk;
    f_pk.close();
    //生成证明
    const r1cs_gg_ppzksnark_proof<default_r1cs_gg_ppzksnark_pp>proof = r1cs_gg_ppzksnark_prover<default_r1cs_gg_ppzksnark_pp>(pk, pb.primary_input(), pb.auxiliary_input());
    //将生成的证明保存到bank_proof.raw文件
    fstream pr("proof.raw", ios_base::out);
    pr<<proof;
    pr.close();
    return 0;
}
