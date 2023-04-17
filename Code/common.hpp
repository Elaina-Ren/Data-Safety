#include<libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include<libsnark/gadgetlib1/pb_variable.hpp>
#include<libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>
using namespace libsnark;
using namespace std;
//定义使用的有限域
typedef libff::Fr<default_r1cs_gg_ppzksnark_pp>FieldT;
//定义创建面包板的函数
protoboard<FieldT>build_protoboard(int* secret){
    //初始化曲线参数
    default_r1cs_gg_ppzksnark_pp::init_public_params();
    //定义面包板
    protoboard<FieldT> pb;
    //定义所有需要外部输入的变量以及中间变量
    pb_variable<FieldT> x;
    pb_variable<FieldT> w_1;
    pb_variable<FieldT> w_2;
    pb_variable<FieldT> w_3;
    pb_variable<FieldT> w_4;
    pb_variable<FieldT> w_5;
    pb_variable<FieldT> out;
   
    //下面将各个变量与 protoboard 连接，相当于把各个元器件插到“面包板”上。allocate() 函数的第二个 string 类型变量仅是用来方便 DEBUG 时的注释，方便 DEBUG 时查看日志。set_input_sizes(n) 用来声明与 protoboard 连接的 public变量的个数 n。在这里 n = 1，表明与 pb 连接的前 n = 1 个变量是 public 的，其余都是 private 的。因此，要将public的变量先与pb连接
    out.allocate(pb, "out");
    x.allocate(pb, "x");
    w_1.allocate(pb, "w_1");
    w_2.allocate(pb, "w_2");
    w_3.allocate(pb, "w_3");
    w_4.allocate(pb, "w_4");
    w_5.allocate(pb, "w_5");
    
    pb.set_input_sizes(1); // 指标为可公开的值
    //为公有变量赋值
    pb.val(out) = 0;//设置具体指标值为99（万元）
   
    //添加一个约束，要求less*1=1，也就是less必须为true。如果是判断小于等于，则添加less_or_eq*1=1的约束
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(x, 1, w_1));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(x, w_1, w_2));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(x, w_2, w_3));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(w_3+w_1, 1, w_4));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(w_4-30, 1, w_5));
    pb.add_r1cs_constraint(r1cs_constraint<FieldT>(w_5, 1, out));
    
    if(secret!=NULL){ // 银行在prove阶段传入secret，其他阶段为NUL
        pb.val(x) = secret[0];
        pb.val(w_1) = secret[1];
        pb.val(w_2) = secret[2];
        pb.val(w_3) = secret[3];
        pb.val(w_4) = secret[4];
        pb.val(w_5) = secret[5];
        
    }
    return pb;
}



