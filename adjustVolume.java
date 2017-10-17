private byte[] adjustVolume(byte[] audioSamples, float volume) {
        byte[] array = new byte[audioSamples.length];
        for (int i = 0; i < array.length; i+=2) {
            // convert byte pair to int
            short buf1 = audioSamples[i+1];
            short buf2 = audioSamples[i];

            buf1 = (short) ((buf1 & 0xff) << 8);
            buf2 = (short) (buf2 & 0xff);

            short res= (short) (buf1 | buf2);
            res = (short) (res * volume);

            // convert back
            array[i] = (byte) res;
            array[i+1] = (byte) (res >> 8);

        }
        return array;
}