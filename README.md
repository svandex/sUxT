# sUxT

基于UxT开发的纯C++虚幻引擎插件

提供的类包括

+ HandPaint：基于LineBatchComponent做的IndexTip画线功能
+ LeftHand：指尖碰撞委托
+ MeshChangeTest：用来测试委托是否发生
+ ButtonBase：增加Visibility函数用于委托，使派生类能在委托发生时隐藏自己
+ PushButton：仿照UxT中的按钮的形状和材质做的纯C++代码的按钮类
+ WorkbenchMapping：在公司做的识别二维码来定位机器人，UDP读取机器人机械臂坐标画出3D曲线的案例

2020/10/30更新：目前还在学习阶段，UxT也在不断更新，本仓库主要还是学习总结，也能给入门者一些案例参考
