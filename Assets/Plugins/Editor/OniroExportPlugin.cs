using UnityEditor;
using System.IO;

public class OniroExportPlugin : IPostprocessBuild
{
    public int callbackOrder => 0;
    
    public void OnPostprocessBuild(BuildReport report)
    {
        if (report.summary.platform == BuildTarget.Android)
        {
            string buildPath = report.summary.outputPath;
            GenerateDevEcoProject(buildPath);
            ConvertAssets(buildPath);
            EditorUtility.DisplayDialog("Oniro Export", "DevEco project generated successfully!", "OK");
        }
    }
    
    private void GenerateDevEcoProject(string buildPath)
    {
        // Generate complete HarmonyOS project structure
        OniroProjectGenerator.Generate(buildPath);
    }
}