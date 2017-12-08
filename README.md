# nanomsg_demo
# 输出目录：  
$(SolutionDir)bin\$(Configuration)

# 中间目录：
$(SolutionDir)build\$(ProjectName)\$(Configuration)

# C/C++
## 附加包含目录：
$(SolutionDir)lib\nanomsg\include

# 链接器
## 附加库目录
$(SolutionDir)lib\nanomsg\lib

## 附加依赖项
nanomsg.lib