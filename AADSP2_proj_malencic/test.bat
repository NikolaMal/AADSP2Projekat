cd D:\AADSP2_ra122_2015\AADSP2_proj_malencic\model0\Debug

"model0.exe" D:\AADSP2_ra122_2015\AADSP2_proj_malencic\TestStreams\titanic_horn.wav D:\AADSP2_ra122_2015\AADSP2_proj_malencic\OutputStreams\output_model0.wav 2 0.5

cd D:\AADSP2_ra122_2015\AADSP2_proj_malencic\model1\Debug

"model1.exe" D:\AADSP2_ra122_2015\AADSP2_proj_malencic\TestStreams\titanic_horn.wav D:\AADSP2_ra122_2015\AADSP2_proj_malencic\OutputStreams\output_model1.wav 2 0.5

cd D:\AADSP2_ra122_2015\tools

"PCMCompare.exe" D:\AADSP2_ra122_2015\AADSP2_proj_malencic\OutputStreams\output_model0.wav D:\AADSP2_ra122_2015\AADSP2_proj_malencic\OutputStreams\output_model1.wav 2>D:\AADSP2_ra122_2015\AADSP2_proj_malencic\compare_output_0_1.txt

cd D:\AADSP2_ra122_2015\AADSP2_proj_malencic\model2\Debug

"model2.exe" D:\AADSP2_ra122_2015\AADSP2_proj_malencic\TestStreams\titanic_horn.wav D:\AADSP2_ra122_2015\AADSP2_proj_malencic\OutputStreams\output_model2.wav 2 0.5

cd D:\AADSP2_ra122_2015\tools

"PCMCompare.exe" D:\AADSP2_ra122_2015\AADSP2_proj_malencic\OutputStreams\output_model0.wav D:\AADSP2_ra122_2015\AADSP2_proj_malencic\OutputStreams\output_model2.wav 2>D:\AADSP2_ra122_2015\AADSP2_proj_malencic\compare_output_0_2.txt