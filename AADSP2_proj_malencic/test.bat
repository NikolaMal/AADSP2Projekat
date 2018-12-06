cd C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\model0\Debug

"model0.exe" C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\TestStreams\titanic_horn.wav C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_model0.wav 2.0 0.5


cd C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\model1\Debug

"model1.exe" C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\TestStreams\titanic_horn.wav C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_model1.wav 2.0 0.5

cd C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\model2\Debug

"model2.exe" C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\TestStreams\titanic_horn.wav C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_model2.wav 2.0 0.5

cd C:\Users\Nikola\Documents\fax\AADSP2-sve\tools

"PCMCompare.exe" C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_model0.wav C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_model1.wav 2>C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_compare_0_1.txt

"PCMCompare.exe" C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_model0.wav C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_model2.wav 2>C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_compare_0_2.txt

"PCMCompare.exe" C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_model1.wav C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_model2.wav 2>C:\Users\Nikola\Documents\fax\AADSP2-sve\AADSP2_proj_malencic\OutputStreams\output_compare_1_2.txt
