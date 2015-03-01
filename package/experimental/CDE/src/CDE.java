package cde;

import android.app.Activity;
import android.os.ServiceManager;
import android.os.Bundle;
import android.os.ICDEService;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class CDE extends Activity implements OnClickListener {
	private final static String LOG_TAG = "CDEActivity";

	private ICDEService cdeService = null;

	private EditText valueText = null;
	private Button readButton = null;
	private Button writeButton = null;
	private Button clearButton = null;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		cdeService = ICDEService.Stub.asInterface(
			ServiceManager.getService("cde"));
			valueText = (EditText)findViewById(R.id.edit_value);
			readButton = (Button)findViewById(R.id.button_read);
			writeButton = (Button)findViewById(R.id.button_write);
			clearButton = (Button)findViewById(R.id.button_clear);

			readButton.setOnClickListener(this);
			writeButton.setOnClickListener(this);
			clearButton.setOnClickListener(this);

			Log.i(LOG_TAG, "Activity created.");
	}

	public void onClick(View v) {
		if(v.equals(readButton)) {
            try {
                String mem = cdeService.read_mem();
                valueText.setText(mem);
            }catch(RemoteException e)
            {
                Log.e(LOG_TAG, "Remote Exception while reading value from cde");
            }
			
		}
		else if(v.equals(writeButton)) {
            try {
                String mem = valueText.getText().toString();
                cdeService.write_mem(mem);
            }catch(RemoteException e)
            {
                Log.e(LOG_TAG, "Remote Exception while writing value to cde");
            }
		}
		else if(v.equals(clearButton)) {
			String text = "";
			valueText.setText(text);
		}
	}
}