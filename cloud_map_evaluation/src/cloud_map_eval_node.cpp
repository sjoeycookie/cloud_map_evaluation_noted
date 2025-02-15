#include "cloud_map_eval.h"
#include <filesystem>



/**t
 *todo  for map evaluation, we have several metrics
 * 1. accuracy p: rmse mean_value
 * 2. completeness r: overlap ratio
 * 3. F1 score: 2pr/(p+r)
 */
int main(int argc, char **argv) {                                           //!主函数
    bool save_immediate_result = true;
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    //* evaluation method, 0: point-to-point icp 1: point-to-plane icp 2: GICP  3:NDT
    int method = 2;
    // int method = 3;
    // max correspondence pairs distance for icp knn search correspondence
    // iteration(the search radius for kdtree)
    //    double icp_max_distance = 1.0;  for large scale outdoor map
    double icp_max_distance = 0.5;

    // set evaluation accuracy level, do not recommend to change, eg. 20cm/10cm/5cm/2cm/1cm
    Vector5d accuracy_level = Vector5d::Zero();
    accuracy_level << 0.2, 0.1, 0.05, 0.02, 0.01;
    //    accuracy_level << 0.5, 0.3, 0.1, 0.05, 0.03;

    //! for map produced by LIO, we need a initial pose
    // we can use cloud compare to align your maps to get the initial pose
    Eigen::Matrix4d initial_matrix = Eigen::Matrix4d::Identity();

    //todo  the path dir must end with '/'
    std::string est_path, gt_path, results_path, sequence_name;
    std::string est_folder = "/home/jhzx/Cloud_Map_Evaluation/cloud_map_evaluation/dataset/";              //使用全局路径才行，不能使用相对路径
    sequence_name = "MCR_slow";
    est_path = est_folder + sequence_name + "/";                                                                                             //*待估计点云存放的工作目录
    gt_path = est_folder + sequence_name + "/" + sequence_name + "_gt.pcd";                            //*真值点云路径
    results_path = est_folder + sequence_name + "/";                                       //*结果路径

    // if you evaluate mme(均值地图熵)
    bool evaluate_mme = false;           
    bool evaluate_gt_mme = false;

    // bool evaluate_mme = true;           
    // bool evaluate_gt_mme = true;

    Param my_param(est_path, gt_path, results_path, initial_matrix, sequence_name,
                   method, icp_max_distance, accuracy_level,
                   save_immediate_result, evaluate_mme, evaluate_gt_mme);          //参数初始化
    CloudMapEva my_evaluation(my_param);    //参数初始化
    my_evaluation.process();  //! 核心函数

    return EXIT_SUCCESS;
}
