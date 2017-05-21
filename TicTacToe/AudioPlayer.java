
import java.io.*;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.swing.*;

public class AudioPlayer  {
		
	public AudioPlayer() {
	
	}
	public void playAudio() {

		try
		{
			File sound = new File("WindowsDing.wav");
			Clip m_clip = AudioSystem.getClip();
			m_clip.open(AudioSystem.getAudioInputStream(getClass().getResource("WindowsDing.wav")));
			m_clip.start();
			Thread.sleep(m_clip.getMicrosecondLength()/10000);
		}
		catch(Exception e)
		{
			JOptionPane.showConfirmDialog(null, e);
		}
	}

}
