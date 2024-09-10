MusInputStream(CodecMus MusInputStream::codecmus, URL url, InputStream inputstream) 
{
        codec = codecmus;
        buffer = new byte[1];
        inputStream = inputstream;
        String s = url.getPath();
        s = s.substring(s.lastIndexOf("/") + 1);
        hash_00 = s.hashCode();
}