using UnityEditor;
using System.IO;

public static class AssetConverter
{
    [MenuItem("Oniro/Convert Assets")]
    public static void ConvertAllAssets()
    {
        ConvertTexturesToASTC();
        ConvertAudioToOgg();
        ConvertShadersToGLES();
        GenerateAssetManifest();
    }
    
    private static void ConvertTexturesToASTC()
    {
        // Convert all textures to ASTC compression for HarmonyOS
        foreach (var texture in Selection.GetFiltered<Texture2D>(SelectionMode.Assets))
        {
            var importer = AssetImporter.GetAtPath(AssetDatabase.GetAssetPath(texture)) as TextureImporter;
            importer.textureCompression = TextureImporterCompression.Compressed;
            importer.crunchedCompression = true;
            importer.SaveAndReimport();
        }
    }
}